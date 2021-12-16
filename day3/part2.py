def filter_by_bit(lines: list[str], position: int, most_often: bool):
  bits = list(map(lambda x: int(x[position]), lines))
  filter_bit = "0"
  if (sum(bits) >= len(lines) / 2) is most_often:
    filter_bit = "1"
  return list(filter(lambda x: x[position] == filter_bit, lines))

with open("data.txt", "r") as file:
  lines = file.readlines()
  oxygen = lines
  carbon = lines

  for i in range(0, len(lines[0]) - 1):
    oxygen = filter_by_bit(oxygen, i, True)
  print(oxygen)

  for i in range(0, len(lines[0]) - 1):
      carbon = filter_by_bit(carbon, i, False)
      if (len(carbon) == 1):
        break
  print(carbon)
    