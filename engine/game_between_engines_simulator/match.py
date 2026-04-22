#!/usr/bin/env python3
"""
UCI Engine Match Simulator
==========================
Simulates N games between two UCI engines using only:
  - uci / isready / position fen <fen> / go movetime <ms>

Each posicion se pasa siempre como FEN completo (sin "moves").

Requiere: pip install chess

Uso:
  python match.py engine1.exe engine2.exe
  python match.py engine1.exe engine2.exe --games 200 --movetime 150
"""

import subprocess
import argparse
import sys
import random
import chess  # pip install chess

# ---------------------------------------------------------------------------
# ~50 posiciones de apertura equilibradas (sin ventaja clara para ningún bando)
# Extraídas de tablas de aperturas teóricas con evaluación cercana a 0.0
# ---------------------------------------------------------------------------
BALANCED_FENS = [
    # Posición inicial
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
    # 1.e4 e5 — Apertura italiana, posición simétrica
    "r1bqk2r/pppp1ppp/2n2n2/2b1p3/2B1P3/2N2N2/PPPP1PPP/R1BQK2R w KQkq - 4 5",
    # Ruy López — posición clásica equilibrada
    "r1bqkb1r/1ppp1ppp/p1n2n2/4p3/B3P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 5",
    # Defensa Siciliana — Variante Najdorf equilibrada
    "rnbqkb1r/1p2pppp/p2p1n2/8/3NP3/2N5/PPP2PPP/R1BQKB1R w KQkq - 0 6",
    # Defensa Francesa — Variante de intercambio
    "rnbqkbnr/ppp2ppp/4p3/3p4/3PP3/8/PPP2PPP/RNBQKBNR w KQkq d6 0 3",
    # Apertura inglesa — c4 c5
    "rnbqkbnr/pp1ppppp/8/2p5/2P5/8/PP1PPPPP/RNBQKBNR w KQkq c6 0 2",
    # Gambito de dama — declinado
    "rnbqkb1r/ppp2ppp/4pn2/3p4/2PP4/2N5/PP2PPPP/R1BQKBNR w KQkq - 2 5",
    # Defensa nimzo-indiana — variante clásica
    "rnbqk2r/pppp1ppp/4pn2/8/1bPP4/2N5/PP2PPPP/R1BQKBNR w KQkq - 2 5",
    # Apertura catalana — abierta
    "rnbqkb1r/ppp2ppp/4pn2/3p4/2PP4/6P1/PP2PP1P/RNBQKBNR w KQkq d6 0 4",
    # Defensa de rey — simétrica
    "rnbqkb1r/pppppp1p/5np1/8/2PP4/8/PP2PPPP/RNBQKBNR w KQkq - 0 3",
    # Apertura española — variante Berlín (muy tablas)
    "r1bqkb1r/pppp1ppp/2n2n2/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4",
    # Defensa siciliana — dragón
    "rnbqkb1r/pp2pp1p/3p1np1/8/3NP3/2N5/PPP2PPP/R1BQKB1R w KQkq - 0 6",
    # Defensa caro-kann — posición clásica
    "rnbqkbnr/pp2pppp/2p5/3p4/3PP3/8/PPP2PPP/RNBQKBNR w KQkq d6 0 3",
    # Apertura de peón de dama — simétrica
    "rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR w KQkq d6 0 2",
    # Defensa holandesa — stonewall
    "rnbqkb1r/ppppp2p/5np1/5p2/2PP4/6P1/PP2PP1P/RNBQKBNR w KQkq f6 0 4",
    # King's Indian — variante clásica
    "rnbqkb1r/pppppp1p/5np1/8/2PP4/2N5/PP2PPPP/R1BQKBNR w KQkq - 2 4",
    # Defensa grünfeld
    "rnbqkb1r/ppp1pp1p/5np1/3p4/2PP4/2N5/PP2PPPP/R1BQKBNR w KQkq d6 0 4",
    # Apertura de cuatro caballos — simétrica
    "r1bqkb1r/pppp1ppp/2n2n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 4 4",
    # Defensa Petrov — simétrica
    "rnbqkb1r/pppp1ppp/8/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 3",
    # Apertura vienesa — simétrica
    "rnbqkbnr/pppp1ppp/8/4p3/4P3/2N5/PPPP1PPP/R1BQKBNR w KQkq e6 0 2",
    # Apertura Réti
    "rnbqkbnr/pppppppp/8/8/8/5N2/PPPPPPPP/RNBQKB1R w KQkq - 2 2",
    # Apertura inglesa — con Nf3
    "rnbqkbnr/pppppppp/8/8/2P5/5N2/PP1PPPPP/RNBQKB1R w KQkq - 2 2",
    # Defensa siciliana — scheveningen
    "rnbqkb1r/pp3ppp/4pn2/2pp4/3PP3/2N2N2/PPP2PPP/R1BQKB1R w KQkq c6 0 6",
    # Gambito de dama aceptado — equilibrado
    "rnbqkbnr/ppp1pppp/8/8/2pP4/8/PP2PPPP/RNBQKBNR w KQkq - 0 3",
    # Defensa Benoni moderna
    "rnbqkb1r/pp1ppppp/2p2n2/8/2PP4/8/PP2PPPP/RNBQKBNR w KQkq - 2 3",
    # Apertura London
    "rnbqkb1r/ppp1pppp/5n2/3p4/3P1B2/5N2/PPP1PPPP/RN1QKB1R w KQkq d6 0 3",
    # Apertura escocesa — simétrica
    "r1bqkbnr/pppp1ppp/2n5/4p3/3PP3/5N2/PPP2PPP/RNBQKB1R w KQkq e6 0 4",
    # Defensa siciliana — kan
    "rnbqkbnr/1p1ppppp/p7/2p5/3PP3/8/PPP2PPP/RNBQKBNR w KQkq c6 0 3",
    # Apertura bird — simétrica
    "rnbqkbnr/pppppppp/8/8/5P2/8/PPPPP1PP/RNBQKBNR w KQkq - 0 1",
    # Defensa pirc
    "rnbqkb1r/ppp1pppp/3p1n2/8/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 2 3",
]

# ---------------------------------------------------------------------------
# Motor UCI
# ---------------------------------------------------------------------------

class UCIEngine:
    def __init__(self, path, name):
        self.name = name
        self.process = subprocess.Popen(
            path,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
            text=True,
            bufsize=1,
        )
        self._init_uci()

    def _send(self, cmd):
        self.process.stdin.write(cmd + "\n")
        self.process.stdin.flush()

    def _read_until(self, keyword, timeout=10):
        import select, time
        lines = []
        deadline = time.time() + timeout
        while time.time() < deadline:
            line = self.process.stdout.readline()
            if not line:
                break
            line = line.strip()
            lines.append(line)
            if line.startswith(keyword):
                return lines
        raise TimeoutError(f"[{self.name}] No recibí '{keyword}' a tiempo")

    def _init_uci(self):
        self._send("uci")
        self._read_until("uciok")
        self._send("isready")
        self._read_until("readyok")

    def get_move(self, fen, movetime):
        """Envía 'position fen <fen>' y 'go movetime <ms>', devuelve movimiento UCI."""
        self._send(f"position fen {fen}")
        self._send(f"go movetime {movetime}")
        lines = self._read_until("bestmove", timeout=movetime / 1000 + 10)
        for line in lines:
            if line.startswith("bestmove"):
                parts = line.split()
                if len(parts) >= 2 and parts[1] not in ("(none)", "0000"):
                    return parts[1]
        return None

    def quit(self):
        try:
            self._send("quit")
            self.process.wait(timeout=5)
        except Exception:
            self.process.kill()


# ---------------------------------------------------------------------------
# Lógica de partida
# ---------------------------------------------------------------------------

def play_game(engine_white, engine_black, start_fen, movetime, max_moves=300):
    """
    Juega una partida completa. Devuelve:
      'white'  — gana blancas
      'black'  — gana negras
      'draw'   — tablas
    """
    board = chess.Board(start_fen)
    move_count = 0

    while not board.is_game_over() and move_count < max_moves:
        current_fen = board.fen()
        engine = engine_white if board.turn == chess.WHITE else engine_black

        move_uci = engine.get_move(current_fen, movetime)
        if move_uci is None:
            # El motor no pudo mover → pierde
            return "black" if board.turn == chess.WHITE else "white"

        try:
            move = chess.Move.from_uci(move_uci)
            if move not in board.legal_moves:
                # Movimiento ilegal → pierde
                return "black" if board.turn == chess.WHITE else "white"
            board.push(move)
        except Exception:
            return "black" if board.turn == chess.WHITE else "white"

        move_count += 1

    if board.is_checkmate():
        return "black" if board.turn == chess.WHITE else "white"
    return "draw"


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(
        description="Simula N partidas entre dos motores UCI"
    )
    parser.add_argument("engine1", help="Ruta al ejecutable del motor 1")
    parser.add_argument("engine2", help="Ruta al ejecutable del motor 2")
    parser.add_argument(
        "--games", type=int, default=100, help="Número de partidas (default: 100)"
    )
    parser.add_argument(
        "--movetime",
        type=int,
        default=100,
        help="Tiempo por movimiento en milisegundos (default: 100)",
    )
    parser.add_argument(
        "--seed", type=int, default=None, help="Semilla para reproducibilidad"
    )
    args = parser.parse_args()

    if args.games < 2:
        print("ERROR: El número de partidas debe ser al menos 2.")
        sys.exit(1)

    if args.seed is not None:
        random.seed(args.seed)

    name1 = args.engine1.split("/")[-1].replace("\\", "/").split("/")[-1]
    name2 = args.engine2.split("/")[-1].replace("\\", "/").split("/")[-1]

    print(f"\n{'='*55}")
    print(f"  Motor 1 : {name1}")
    print(f"  Motor 2 : {name2}")
    print(f"  Partidas: {args.games}  |  Tiempo/mov: {args.movetime} ms")
    print(f"{'='*55}\n")

    print("Iniciando motores...", end=" ", flush=True)
    try:
        engine1 = UCIEngine(args.engine1, name1)
        engine2 = UCIEngine(args.engine2, name2)
    except Exception as e:
        print(f"\nERROR al iniciar motores: {e}")
        sys.exit(1)
    print("OK\n")

    wins1 = wins2 = draws = 0
    fens = BALANCED_FENS.copy()

    try:
        for game_num in range(1, args.games + 1):
            # Alternar colores cada partida
            if game_num % 2 == 1:
                white_engine, black_engine = engine1, engine2
                white_label, black_label = "Motor1", "Motor2"
            else:
                white_engine, black_engine = engine2, engine1
                white_label, black_label = "Motor2", "Motor1"

            start_fen = fens[(game_num - 1) % len(fens)];

            result = play_game(
                white_engine, black_engine, start_fen, args.movetime
            )

            if result == "white":
                if white_label == "Motor1":
                    wins1 += 1
                else:
                    wins2 += 1
            elif result == "black":
                if black_label == "Motor1":
                    wins1 += 1
                else:
                    wins2 += 1
            else:
                draws += 1

            total = wins1 + wins2 + draws
            pct1 = (wins1 + 0.5 * draws) / total * 100
            bar = int(pct1 / 2)
            bar_str = "█" * bar + "░" * (50 - bar)
            print(
                f"\r  Partida {game_num:>5}/{args.games}"
                f"  |  {name1[:15]}: {wins1}  Tablas: {draws}  {name2[:15]}: {wins2}"
                f"  |  {pct1:.1f}%",
                end="",
                flush=True,
            )
    except KeyboardInterrupt:
        print("\n\nInterrumpido por el usuario.")

    print("\n")
    total = wins1 + wins2 + draws
    if total == 0:
        print("No se jugó ninguna partida.")
    else:
        pct1 = (wins1 + 0.5 * draws) / total * 100
        pct2 = (wins2 + 0.5 * draws) / total * 100

        print(f"{'='*55}")
        print(f"  RESULTADOS FINALES  ({total} partidas)")
        print(f"{'='*55}")
        print(f"  {name1:<30} {wins1:>5} victorias  ({pct1:.1f}%)")
        print(f"  Tablas                         {draws:>5}")
        print(f"  {name2:<30} {wins2:>5} victorias  ({pct2:.1f}%)")
        print(f"{'='*55}\n")

        if pct1 > pct2:
            print(f"  ► Mejor motor: {name1}  (+{pct1-pct2:.1f}%)")
        elif pct2 > pct1:
            print(f"  ► Mejor motor: {name2}  (+{pct2-pct1:.1f}%)")
        else:
            print("  ► Resultado completamente igualado.")
        print()

    engine1.quit()
    engine2.quit()


if __name__ == "__main__":
    main()
