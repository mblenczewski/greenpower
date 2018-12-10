from Python.Utils.GUI import App, Window
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QAction, qApp, QPushButton, QSizePolicy
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import sys


class MonitorApp(App):
    """
    A class for the monitoring app.
    """
    def show_window(self):
        _ = MainView()
        sys.exit(self.exec_())


class MainView(Window):
    """
    A class for the start screen of the monitor app.
    """

    def init_ui(self):
        """ Lays out and shows the main window of the app. """
        # sets up the action to exit the app through the menu
        exit_act = QAction(QIcon('exit.png'), '&Exit', self)
        exit_act.setShortcut('Ctrl+Q')
        exit_act.setStatusTip('Exit application')
        exit_act.triggered.connect(qApp.quit)

        # idk
        self.statusBar()

        # creates the menubar and adds options
        menubar = self.menuBar()
        file_menu = menubar.addMenu('&Options')
        file_menu.addAction(exit_act)

        # adds buttons to launch the other widgets

        # shows the window
        self.show()


class BatteryView(Window):
    """
    A class for the batter view of the monitor app.
    """

    def init_ui(self):
        m = self.PlotCanvas(self, width=5, height=4)
        m.move(0, 0)

        button = QPushButton('PyQt5 button', self)
        button.setToolTip('This s an example button')
        button.move(500, 0)
        button.resize(140, 100)

        self.show()


class LocationView(Window):
    """
    A class for the track render of the monitor app.
    """


class SerialViewer(Window):
    """
    A class for the serial IO viewer of the monitor app.
    """


class PlotCanvas(FigureCanvas):
    """
    A class that encompasses a line graph with many plotted points.
    """
    def __init__(self, parent=None, width=5, height=4, dpi=100):
        fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = fig.add_subplot(111)

        FigureCanvas.__init__(self, fig)
        self.setParent(parent)

        FigureCanvas.setSizePolicy(self, QSizePolicy.Expanding, QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)
        self.plot()

    def plot(self):
        data = [random.random() for i in range(25)]
        ax = self.figure.add_subplot(111)
        ax.plot(data, 'r-')
        ax.plot([0, 25], [1, 0], color='b')
        ax.set_title('Battery')
        self.draw()
