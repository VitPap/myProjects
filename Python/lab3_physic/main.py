import numpy as np
from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt

def cycloid(radius, speed, t):
    x = speed * t - radius * np.sin(speed * t / radius)
    y = radius - radius * np.cos(speed * t / radius)
    return x, y

radius = float(input("Радиус колеса: "))
speed = float(input("Скорость центра масс: "))

figure, space = plt.subplots()
space.set_aspect('equal')
space.set_xlim(0, 20)
space.set_ylim(-2.5 * radius, 2.5 * radius)

line, = space.plot([], [], lw=2)

def start_func():
    line.set_data([], [])
    return line,

def update(frame):
    t = np.linspace(0, frame, 50)
    x, y = cycloid(radius, speed, t)
    line.set_data(x, y)
    return line,

ani = FuncAnimation(figure, update, frames=np.linspace(0, 20, 200), init_func=start_func)

plt.show()
