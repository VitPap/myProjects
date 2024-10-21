import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import math

def get_positive_float(prompt):
    while True:
        try:
            value = float(input(prompt))
            if value > 0:
                return value
            else:
                print("Ошибка: значение должно быть положительным числом.")
        except ValueError:
            print("Ошибка: введите корректное число.")

def get_position(prompt, min_val, max_val):
    while True:
        try:
            value = float(input(prompt))
            if min_val <= value <= max_val:
                return value
            else:
                print(f"Ошибка: значение должно быть в пределах от {min_val} до {max_val}.")
        except ValueError:
            print("Ошибка: введите корректное число.")

def get_angle(prompt):
    while True:
        try:
            value = float(input(prompt))
            if 0 <= value < 360:
                return value
            else:
                print("Ошибка: угол должен быть в пределах от 0 до 360 градусов.")
        except ValueError:
            print("Ошибка: введите корректное число.")

r1 = 10.0
r2 = 10.0

m1 = get_positive_float("Введите массу первого тела: ")
m2 = get_positive_float("Введите массу второго тела: ")

box_width = get_positive_float("Введите ширину прямоугольной оболочки: ")
box_height = get_positive_float("Введите высоту прямоугольной оболочки: ")

min_box_size = min(box_width, box_height)
if r1 > min_box_size / 2 or r2 > min_box_size / 2:
    raise ValueError("Радиусы тел не могут превышать половину минимального размера оболочки.")

speed1 = get_positive_float("Введите модуль начальной скорости первого тела: ")
angle1 = get_angle("Введите угол направления скорости первого тела (в градусах): ")

speed2 = get_positive_float("Введите модуль начальной скорости второго тела: ")
angle2 = get_angle("Введите угол направления скорости второго тела (в градусах): ")

v1_x = speed1 * math.cos(math.radians(angle1))
v1_y = speed1 * math.sin(math.radians(angle1))
v2_x = speed2 * math.cos(math.radians(angle2))
v2_y = speed2 * math.sin(math.radians(angle2))

pos1_x = get_position("Введите начальную позицию по оси X первого тела: ", r1, box_width - r1)
pos1_y = get_position("Введите начальную позицию по оси Y первого тела: ", r1, box_height - r1)
pos2_x = get_position("Введите начальную позицию по оси X второго тела: ", r2, box_width - r2)
pos2_y = get_position("Введите начальную позицию по оси Y второго тела: ", r2, box_height - r2)

pos1 = np.array([pos1_x, pos1_y])
pos2 = np.array([pos2_x, pos2_y])
distance_between_bodies = np.linalg.norm(pos1 - pos2)

if distance_between_bodies < r1 + r2:
    raise ValueError("Тела не могут изначально пересекаться или касаться друг друга.")

v1 = np.array([v1_x, v1_y])
v2 = np.array([v2_x, v2_y])
box_size = np.array([box_width, box_height])

def update(pos1, pos2, v1, v2, dt):
    pos1 += v1 * dt
    pos2 += v2 * dt

    for i in range(2):
        if pos1[i] - r1 < 0 or pos1[i] + r1 > box_size[i]:
            v1[i] *= -1
        if pos2[i] - r2 < 0 or pos2[i] + r2 > box_size[i]:
            v2[i] *= -1

    dist = np.linalg.norm(pos1 - pos2)
    if dist < r1 + r2:
        normal = (pos2 - pos1) / dist
        v1_proj = np.dot(v1, normal)
        v2_proj = np.dot(v2, normal)
        v1_new = (v1_proj * (m1 - m2) + 2 * m2 * v2_proj) / (m1 + m2)
        v2_new = (v2_proj * (m2 - м1) + 2 * м1 * v1_proj) / (м1 + м2)
        v1 += (v1_new - v1_proj) * normal
        v2 += (v2_new - v2_proj) * normal

    return pos1, pos2, v1, v2

fig, ax = plt.subplots()
ax.set_xlim(0, box_size[0])
ax.set_ylim(0, box_size[1])
body1, = plt.plot([], [], 'ro', ms=10)
body2, = plt.plot([], [], 'bo', ms=10)
dt = 0.01

def init():
    body1.set_data([], [])
    body2.set_data([], [])
    return body1, body2

def animate(frame):
    global pos1, pos2, v1, v2
    pos1, pos2, v1, v2 = update(pos1, pos2, v1, v2, dt)
    body1.set_data(pos1[0], pos1[1])
    body2.set_data(pos2[0], pos2[1])
    return body1, body2

ani = FuncAnimation(fig, animate, frames=200, init_func=init, interval=20, blit=True)
plt.show()
