from tqdm import tqdm
import pandas

PATH_TO_HEADER_FILE = "./fair_positions.h"
FENS_TO_RETREIVE = 2000
ANALYSIS_THRESHOLD = 1

fen_analysis = pandas.read_csv("./fen_analysis.csv")

header_file = open(PATH_TO_HEADER_FILE, "w")

header_file.write(
"""#include <string>
#include <vector>

const std::vector<std::string> fair_positions = {"""
)

counter = 0
progress = tqdm(total=FENS_TO_RETREIVE)

for i, row in fen_analysis.iterrows():
    fen = row["FEN"]
    analysis = row["Analysis"]

    if abs(analysis) > ANALYSIS_THRESHOLD:
        continue

    header_file.write(f"\"{fen}\"")

    if counter < FENS_TO_RETREIVE - 1:
        header_file.write(", ")

    if counter % 3 == 2:
        header_file.write("\n")
    
    counter += 1
    
    if counter >= FENS_TO_RETREIVE:
        break

    progress.update()

header_file.write("};")
header_file.close()