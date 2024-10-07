import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

m1 = float(input("Введите массу первого тела: "))
m2 = float(input("Введите массу второго тела: "))
r1 = float(input("Введите радиус первого тела: "))
r2 = float(input("Введите радиус второго тела: "))

v1_x = float(input("Введите начальную скорость по оси X первого тела: "))
v1_y = float(input("Введите начальную скорость по оси Y первого тела: "))
v2_x = float(input("Введите начальную скорость по оси X второго тела: "))
v2_y = float(input("Введите начальную скорость по оси Y второго тела: "))

pos1_x = float(input("Введите начальную позицию по оси X первого тела: "))
pos1_y = float(input("Введите начальную позицию по оси Y первого тела: "))
pos2_x = float(input("Введите начальную позицию по оси X второго тела: "))
pos2_y = float(input("Введите начальную позицию по оси Y второго тела: "))

box_width = float(input("Введите ширину прямоугольной оболочки: "))
box_height = float(input("Введите высоту прямоугольной оболочки: "))

v1 = np.array([v1_x, v1_y])
v2 = np.array([v2_x, v2_y])
pos1 = np.array([pos1_x, pos1_y])
pos2 = np.array([pos2_x, pos2_y])
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
        v2_new = (v2_proj * (m2 - m1) + 2 * m1 * v1_proj) / (m1 + m2)
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
