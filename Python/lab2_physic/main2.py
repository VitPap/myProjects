import numpy as np
import matplotlib.pyplot as plt

def speed_in_time(sx, sy, time, g=9.81):
    fy = sy - g * time
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

def get_positive_float(prompt):
    """Запрашивает у пользователя положительное число с обработкой ошибок."""
    while True:
        try:
            value = float(input(prompt))
            if value > 0:
                return value
            else:
                print("Ошибка: введите положительное число.")
        except ValueError:
            print("Ошибка: введите корректное число.")

def get_angle(prompt):
    """Запрашивает у пользователя угол в диапазоне от 0 до 90 с обработкой ошибок."""
    while True:
        try:
            value = float(input(prompt))
            if 0 < value <= 90:
                return value
            else:
                print("Ошибка: угол должен быть в диапазоне от 0 до 90 градусов.")
        except ValueError:
            print("Ошибка: введите корректное число.")

height = get_positive_float("Высота с которой брошено тело (в м): ")
speed = get_positive_float("Начальная скорость тела (в м/с): ")
angle = get_angle("Угол броска тела (в градусах): ")

sp_x = speed * np.cos(np.radians(angle))
sp_y = speed * np.sin(np.radians(angle))

time_values, x_values, y_values = calc_path(height, speed, angle)

speeds = []
speeds_x = []
speeds_y = []
for time in time_values:
    speeds.append(speed_in_time(sp_x, sp_y, time))
    speeds_x.append(sp_x)  
    speeds_y.append(sp_y - 9.81 * time)

plt.figure(figsize=(12, 8))

plt.subplot(3, 2, 1)
plt.plot(x_values, y_values)
plt.xlabel("Расстояние (м)")
plt.ylabel("Высота (м)")
plt.title("Визуализация траектории движения тела")
plt.grid(True)
plt.xlim(0, 100)  
plt.ylim(0, 60)   

plt.subplot(3, 2, 3)
plt.plot(time_values, x_values)
plt.xlabel("Время (с)")
plt.ylabel("Координата x (м)")
plt.title("Зависимость координаты x от времени")
plt.grid(True)
plt.xlim(0, 4)    
plt.ylim(0, 40)   

plt.subplot(3, 2, 5)
plt.plot(time_values, y_values)
plt.xlabel("Время (с)")
plt.ylabel("Координата y (м)")
plt.title("Зависимость координаты y от времени")
plt.grid(True)
plt.xlim(0, 4)    
plt.ylim(0, 60)   

plt.subplot(3, 2, 2)
plt.plot(time_values, speeds_x)
plt.xlabel("Время (с)")
plt.ylabel("Скорость по координате x (м/с)")
plt.title("Зависимость скорости по координате x от времени")
plt.grid(True)
plt.xlim(0, 4)    
plt.ylim(9, 10)   

plt.subplot(3, 2, 4)
plt.plot(time_values, speeds_y)
plt.xlabel("Время (с)")
plt.ylabel("Скорость по координате y (м/с)")
plt.title("Зависимость скорости по координате y от времени")
plt.grid(True)
plt.xlim(0, 4)    
plt.ylim(-50, 50) 

plt.tight_layout()
plt.show()
