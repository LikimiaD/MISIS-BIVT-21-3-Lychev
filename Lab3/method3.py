import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

def f(x, y):
    return (x + y)**2 + np.sin(x + 2)**2 + y**2

def main():
    x_vals = np.loadtxt('x_vals.txt')
    y_vals = np.loadtxt('y_vals.txt')

    z_vals = f(x_vals, y_vals)

    X = np.linspace(min(x_vals)-1, max(x_vals)+1, 400)
    Y = np.linspace(min(y_vals)-1, max(y_vals)+1, 400)
    X, Y = np.meshgrid(X, Y)
    Z = f(X, Y)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    traj = ax.plot(x_vals, y_vals, z_vals, color='r', label='Траектория', alpha=1, marker='o', markersize=3)
    surf = ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.6, edgecolor='none')

    ax.legend()
    ax.set_xlabel('Ось X')
    ax.set_ylabel('Ось Y')
    ax.set_zlabel('f(X, Y)')
    plt.title('Траектория метода Ньютона')
    plt.savefig('img/method3.png')

if __name__ == '__main__':
    main()