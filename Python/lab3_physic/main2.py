import numpy as np
from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt

def cycloid(radius, speed, t):
    x = speed * t - radius * np.sin(speed * t / radius)
    y = radius - radius * np.cos(speed * t / radius)
    return x, y

def validate_input(prompt, condition, error_message):
    while True:
        try:
            value = float(input(prompt))
            if condition(value):
                return value
            else:
                print(error_message)
        except ValueError:
            print("Ошибка: введите числовое значение.")

radius = validate_input(
    "Радиус колеса: ",
    lambda r: r > 0,
    "Ошибка: радиус должен быть положительным числом."
)

speed = validate_input(
    "Скорость центра масс: ",
    lambda v: v != 0,
    "Ошибка: скорость не может быть равной нулю."
)

figure, space = plt.subplots()
space.set_aspect('equal')

space.set_xlim(0, 20)  # Фиксируем ось x от 0 до 20
space.set_ylim(-10, 10)  # Фиксируем ось y от -10 до 10

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
