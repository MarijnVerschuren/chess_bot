import subprocess
import time

p = subprocess.Popen(["chess_bot",], stdin=subprocess.PIPE, executable="cmake-build-debug/chess_bot")
p.stdin.write(b"hi")

time.sleep(1)

#print(p.stdout)
