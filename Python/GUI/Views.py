from Python.Utils.GUI import App, Window
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QAction, qApp, QPushButton, QSizePolicy
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import sys, random


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

    def __init__(self):
        super().__init__(width=500, height=120)
        self.battery_view = BatteryView()
        self.location_view = LocationView()
        self.serial_view = SerialView()

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

        # sets up battery view related things
        to_battery_view_btn = QPushButton("Open Battery Viewer", self)
        to_battery_view_btn.setToolTip("Opens the Battery Viewer")
        to_battery_view_btn.move(10, 60)
        to_battery_view_btn.resize(150, 50)
        to_battery_view_btn.clicked.connect(lambda: self.battery_view.show())

        # sets up racetrack view related things
        to_location_view_btn = QPushButton("Open Racetrack Viewer", self)
        to_location_view_btn.setToolTip("Opens the Racetrack Viewer")
        to_location_view_btn.move(170, 60)
        to_location_view_btn.resize(150, 50)
        to_location_view_btn.clicked.connect(lambda: self.location_view.show())

        # sets up serial io view related things
        to_serial_view_btn = QPushButton("Open Serial IO Viewer", self)
        to_serial_view_btn.setToolTip("Opens the Serial IO Viewer")
        to_serial_view_btn.move(330, 60)
        to_serial_view_btn.resize(150, 50)
        to_serial_view_btn.clicked.connect(lambda: self.serial_view.show())

        # shows the window
        self.show()


class BatteryView(Window):
    """
    A class for the batter view of the monitor app.
    """

    def __init__(self):
        super().__init__(title="Battery View", width=300, height=300)

    def init_ui(self):
        m = PlotCanvas(self, width=5, height=4)
        m.move(0, 0)

    def closeEvent(self, event):
        event.accept()


class LocationView(Window):
    """
    A class for the track render of the monitor app.
    """

    def __init__(self):
        super().__init__(title="Racetrack View", width=300, height=300)

    def init_ui(self):
        pass

    def closeEvent(self, event):
        event.accept()


class SerialView(Window):
    """
    A class for the serial IO viewer of the monitor app.
    """

    def __init__(self):
        super().__init__(title="Serial IO View", width=300, height=300)

    def init_ui(self):
        pass

    def closeEvent(self, event):
        event.accept()


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
