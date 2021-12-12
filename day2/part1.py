from functools import reduce

forward = 0
back = 0
down = 0
up = 0

def get_sum(command: str, commands):
  return reduce(lambda accum, x: int(x[1]) + accum, filter(lambda x: x[0] == command, commands), 0)

with open("data.txt") as file:
  lines = file.readlines();
  commands = list(map(lambda x: x.split(" "), lines))
  forwards = get_sum("forward", commands)
  downs = get_sum("down", commands)
  ups = get_sum("up", commands)
  

print(forwards, ups, downs)
print(forwards* (downs-ups))