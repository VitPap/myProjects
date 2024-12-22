import numpy as np
import matplotlib.pyplot as plt

def calculate_field_lines(epsilon1, epsilon2, E0, angle_E0, n_lines=10):
    angle_E0_rad = np.radians(angle_E0)
    E0_x = E0 * np.cos(angle_E0_rad)
    E0_y = E0 * np.sin(angle_E0_rad)

    lines = []
    for i in range(n_lines):
        offset = (i - n_lines // 2) * 0.1
        start_x = offset
        start_y = -1

        if epsilon1 != epsilon2:
            tan_theta1 = E0_y / E0_x if E0_x != 0 else np.inf
            tan_theta2 = (epsilon1 / epsilon2) * tan_theta1
            if E0_x != 0:
                x_boundary = start_x + (0 - start_y) / tan_theta1
                y_boundary = 0

                end_x = x_boundary + (1 - y_boundary) * tan_theta2
                end_y = 1
            else:
                x_boundary = start_x
                y_boundary = 0

                end_x = start_x
                end_y = 1
        else:
            x_boundary = start_x
            y_boundary = 0
            end_x = start_x
            end_y = 1

        lines.append(((start_x, start_y), (x_boundary, y_boundary), (end_x, end_y)))
    return lines

def plot_field_lines(lines):
    fig, ax = plt.subplots(figsize=(8, 6))

    ax.axhline(0, color='black', linewidth=0.8, label="Граница раздела сред")
    ax.axvline(0, color='black', linewidth=0.8)

    for line in lines:
        (x1, y1), (x2, y2), (x3, y3) = line
        ax.plot([x1, x2], [y1, y2], color='blue', label='Линии напряженности (в первой среде)' if line == lines[0] else "")
        ax.plot([x2, x3], [y2, y3], color='red', label='Линии напряженности (во второй среде)' if line == lines[0] else "")

    ax.set_xlim(-1.5, 1.5)
    ax.set_ylim(-1.5, 1.5)
    ax.set_aspect('equal')
    ax.legend()
    ax.set_title("Преломление линий напряженности и электрического смещения")
    ax.set_xlabel("Координата x")
    ax.set_ylabel("Координата y")
    plt.show()

while True:
    try:
        epsilon1 = float(input("Введите диэлектрическую проницаемость первой среды (положительное число): "))
        if epsilon1 <= 0:
            raise ValueError("Проницаемость должна быть положительным числом.")
        break
    except ValueError as e:
        print(e)

while True:
    try:
        epsilon2 = float(input("Введите диэлектрическую проницаемость второй среды (положительное число): "))
        if epsilon2 <= 0:
            raise ValueError("Проницаемость должна быть положительным числом.")
        break
    except ValueError as e:
        print(e)

while True:
    try:
        E0 = float(input("Введите величину напряженности электрического поля (положительное число): "))
        if E0 <= 0:
            raise ValueError("Напряженность должна быть положительным числом.")
        break
    except ValueError as e:
        print(e)

while True:
    try:
        angle_E0 = float(input("Введите угол электрического поля (от 0 до 360 градусов): "))
        if not (0 <= angle_E0 <= 360):
            raise ValueError("Угол должен быть в диапазоне от 0 до 360 градусов.")
        break
    except ValueError as e:
        print(e)

lines = calculate_field_lines(epsilon1, epsilon2, E0, angle_E0)
plot_field_lines(lines)