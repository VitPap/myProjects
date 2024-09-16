import numpy as np
import matplotlib.pyplot as plt

def speed_in_time(sx, sy, time):
    fy = sy - 9.81 * time
    return np.sqrt(sx**2 + fy**2)

def calc_path(height, start_speed, angle, g=9.81, dt=0.01):
    angle_rad = np.radians(angle)

    sp_x = start_speed * np.cos(angle_rad)
    sp_y = start_speed * np.sin(angle_rad)

    time_flight = np.sqrt(sp_y**2 + 2 * g * height)
    time_flight = (sp_y + time_flight) / g

    time_values = np.arange(0, time_flight, dt)

    x_values = sp_x * time_values
    y_values = sp_y * time_values + height - (g * time_values**2)/2

    return time_values, x_values, y_values

height = float(input("Высота с которой брошено тело(в м): "))
speed = float(input("Начальная скорость тела(в м/с): "))
angle = float(input("Угол броска тела(в градусах): "))

sp_x = speed * np.cos(np.radians(angle))
sp_y = speed * np.sin(np.radians(angle))

time_values, x_values, y_values = calc_path(height, speed, angle)

speeds = []
for time in time_values:
    speeds.append(speed_in_time(time, sp_x, sp_y))

plt.figure(figsize=(14, 6))

plt.xlabel("Координата x(м)")
plt.ylabel("Координата y(м)")
plt.subplot(2, 2, 1)
plt.plot(x_values, y_values)
plt.title("Траектория движения тела")

plt.xlabel("Время(с)")
plt.ylabel("Скорость(м/с)")
plt.subplot(2, 2, 2)
plt.plot(time_values, speeds)
plt.title("График зависимости скорости от времени")


plt.xlabel("Время(с)")
plt.ylabel("Координата x(м)")
plt.subplot(2, 2, 3)
plt.plot(time_values, x_values)
plt.title("График зависимости координаты x от времени")


plt.xlabel("Время(с)")
plt.ylabel("Координата y(м)")
plt.subplot(2, 2, 4)
plt.plot(time_values, y_values)
plt.title("График зависимости координаты y от времени")


plt.tight_layout()
plt.show()
