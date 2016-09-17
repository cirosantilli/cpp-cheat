import numpy
def plot(plt, data_path):
    a = numpy.loadtxt(data_path, skiprows=1, usecols=(0, 4))
    plt.plot(
        a[:, 0],
        a[:, 1],
        'x',
        label='collision'
    )
