import tkinter as tk
from tkinter import messagebox
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# Глобальные параметры для схем
NUM_RESISTORS = 3
NUM_EMFS = 2

SCHEMES = {
    "Схема 1 (последовательная с двумя ЭДС)": {"resistors": 3, "emfs": 2},
    "Схема 2 (последовательная с одним ЭДС)": {"resistors": 3, "emfs": 1},
    "Схема 3 (параллельная)": {"resistors": 2, "emfs": 1},
    "Схема 4 (сложная схема)": {"resistors": 4, "emfs": 2},
}

# Функция для расчета тока в цепи
def solve_circuit(resistances, emfs):
    total_resistance = sum(resistances)
    total_emf = sum(emfs)  # Считаем, что источники ЭДС соединены последовательно
    current = total_emf / total_resistance  # I = E / R
    return current

# Функция для визуализации электрической схемы
def visualize_circuit(resistances, emfs, frame, scheme_name):
    G = nx.Graph()

    # Получаем настройки для текущей схемы
    scheme = SCHEMES[scheme_name]
    num_resistors = scheme["resistors"]
    num_emfs = scheme["emfs"]

    # Добавляем узлы для источников ЭДС
    for i in range(num_emfs):
        G.add_node(f"EMF{i+1}", label=f"EMF{i+1}: {emfs[i] if i < len(emfs) else 0}V")
    
    # Добавляем узлы для резисторов
    for i in range(num_resistors):
        G.add_node(f"R{i+1}", label=f"R{i+1}: {resistances[i] if i < len(resistances) else 0}Ω")
    
    # Создаем соединения в зависимости от типа схемы
    if scheme_name == "Схема 1 (последовательная с двумя ЭДС)":
        for i in range(num_emfs - 1):
            G.add_edge(f"EMF{i+1}", f"EMF{i+2}")
        if num_emfs > 0 and num_resistors > 0:
            G.add_edge(f"EMF{num_emfs}", "R1")
        for i in range(num_resistors - 1):
            G.add_edge(f"R{i+1}", f"R{i+2}")
    elif scheme_name == "Схема 2 (последовательная с одним ЭДС)":
        if num_emfs > 0:
            G.add_edge("EMF1", "R1")
        for i in range(num_resistors - 1):
            G.add_edge(f"R{i+1}", f"R{i+2}")
    elif scheme_name == "Схема 3 (параллельная)":
        if num_emfs > 0:
            G.add_edge("EMF1", "R1")
            G.add_edge("EMF1", "R2")
    elif scheme_name == "Схема 4 (сложная схема)":
        if num_emfs > 0:
            G.add_edge("EMF1", "R1")
            G.add_edge("EMF2", "R2")
        G.add_edge("R1", "R3")
        G.add_edge("R2", "R4")
        G.add_edge("R3", "R4")

    pos = nx.spring_layout(G, seed=42)

    # Рисуем граф
    plt.figure(figsize=(8, 6))
    nx.draw_networkx_nodes(G, pos, node_size=700, node_color='skyblue')
    nx.draw_networkx_edges(G, pos, width=2, alpha=0.7, edge_color='black')

    # Добавляем подписи узлов
    labels = nx.get_node_attributes(G, 'label')
    nx.draw_networkx_labels(G, pos, labels=labels, font_size=10, font_color="black")

    plt.title(scheme_name)
    plt.axis('off')

    # Удаляем старую схему и обновляем
    for widget in frame.winfo_children():
        widget.destroy()
    canvas = FigureCanvasTkAgg(plt.gcf(), master=frame)
    canvas.draw()
    canvas.get_tk_widget().grid(row=0, column=0)

# Функция для обновления интерфейса в зависимости от выбранной схемы
def update_scheme(*args):
    global NUM_RESISTORS, NUM_EMFS
    scheme_name = scheme_var.get()
    scheme = SCHEMES[scheme_name]
    NUM_RESISTORS = scheme["resistors"]
    NUM_EMFS = scheme["emfs"]

    # Обновляем подсказки для ввода данных
    resistance_label.config(text=f"Введите сопротивления резисторов (через запятую, {NUM_RESISTORS} значения):")
    emf_label.config(text=f"Введите ЭДС (через запятую, {NUM_EMFS} значения):")

    # Обновляем начальную схему
    visualize_circuit([], [], frame_canvas, scheme_name)

# Функция для обработки ввода данных и отображения результатов
def on_calculate():
    try:
        # Получаем данные
        resistances = list(map(float, resistance_entry.get().split(',')))
        emfs = list(map(float, emf_entry.get().split(',')))

        # Проверяем количество введенных данных
        if len(resistances) != NUM_RESISTORS or len(emfs) != NUM_EMFS:
            messagebox.showerror(
                "Ошибка",
                f"Неверное количество значений. Нужно ввести {NUM_RESISTORS} сопротивлений и {NUM_EMFS} ЭДС."
            )
            return

        # Решаем задачу
        current = solve_circuit(resistances, emfs)
        result_label.config(text=f"Ток в цепи: {current:.2f} A")

        # Обновляем схему
        visualize_circuit(resistances, emfs, frame_canvas, scheme_var.get())
    except ValueError:
        messagebox.showerror("Ошибка", "Некорректный ввод данных. Убедитесь, что все значения числовые.")
    except Exception as e:
        messagebox.showerror("Ошибка", f"Произошла ошибка: {e}")

# Создаем графическое окно с использованием Tkinter
root = tk.Tk()
root.title("Расчет токов в электрической цепи")

# Размер окна
root.geometry("900x800")

# Выпадающий список для выбора схемы
scheme_var = tk.StringVar()
scheme_var.set(list(SCHEMES.keys())[0])  # Устанавливаем схему по умолчанию
scheme_menu = tk.OptionMenu(root, scheme_var, *SCHEMES.keys(), command=update_scheme)
scheme_menu.pack(pady=10)

# Фрейм для ввода данных
frame_input = tk.Frame(root)
frame_input.pack(pady=20)

# Ввод сопротивлений
resistance_label = tk.Label(frame_input, text="")
resistance_label.grid(row=0, column=0, padx=5, pady=5)
resistance_entry = tk.Entry(frame_input, width=30)
resistance_entry.grid(row=0, column=1, padx=5, pady=5)

# Ввод ЭДС
emf_label = tk.Label(frame_input, text="")
emf_label.grid(row=1, column=0, padx=5, pady=5)
emf_entry = tk.Entry(frame_input, width=30)
emf_entry.grid(row=1, column=1, padx=5, pady=5)

# Кнопка для расчета
calculate_button = tk.Button(frame_input, text="Рассчитать", command=on_calculate, height=2, width=15)
calculate_button.grid(row=2, columnspan=2, pady=20)

# Результат
result_label = tk.Label(root, text="Результат будет отображен здесь.", font=("Helvetica", 14))
result_label.pack(pady=20)

# Фрейм для отображения схемы
frame_canvas = tk.Frame(root)
frame_canvas.pack(pady=20)

# Изначально отображаем пустую схему
update_scheme()

# Запуск приложения
root.mainloop()
