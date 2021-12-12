from functools import reduce

def aim(status: [int, int, int], command: [str, str]):
  position, depth, aim = status
  direction, amount = command
  print(status, command)
  amount = int(amount)
  if direction == "forward":
    depth += amount * aim
    position += amount
  elif direction == "down":
    aim += amount
  elif direction == "up":
    aim -= amount
    depth = max(depth, 0)
  return [position, depth, aim]


with open("data.txt") as file:
  lines = file.readlines();
  commands = list(map(lambda x: x.split(" "), lines))

horiz, depth, aim = reduce(aim, commands, [0, 0, 0])
print(horiz*depth)