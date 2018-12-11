from Python.Utils.GUI import App, Window
from Python.Utils.ListTools import batch
from typing import List, Tuple
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QAction, qApp, QPushButton, QSizePolicy
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
from datetime import datetime
import matplotlib.pyplot
import sys
import random
import queue


class MonitorApp(App):
    """
    A class for the monitoring app.
    """
    def show_window(self):
        matplotlib.pyplot.ion() # turns on interactive mode for plots
        _ = MainView()
        sys.exit(self.exec_())


class MainView(Window):
    """
    A class for the start screen of the monitor app.
    """

    def __init__(self):
        super().__init__(width=490, height=120)
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
        # self.statusBar()

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

    def show_battery_view(self):
        self.battery_view.show()

    def show_location_view(self):
        self.location_view.show()

    def show_serial_view(self):
        self.serial_view.show()


class BatteryView(Window):
    """
    A class for the batter view of the monitor app.
    """

    MAX_CURRENT = 100
    """ The maximum current draw in amps the battery might experience. """

    MIN_CURRENT = -100
    """ The maximum negative current draw in amps the battery might experience. """

    def __init__(self):
        super().__init__(title="Battery View", width=500, height=500)
        self.data_points: queue.Queue = queue.Queue

    def init_ui(self):
        plot = BatteryCurrentPlot(self)
        plot.move(0, 0)
        self.data_points = [(random.random(), datetime.now()) for _ in range(7200)]
        # plot.plot_data(points)
        plot.plot_data(self.data_points, "b-", 0.5, 5)

    def add_point(self, point: (int, datetime)):
        """ Adds a point to the battery graph. """
        self.data_points.put(point, False)

    def closeEvent(self, event):
        event.accept()


class LocationView(Window):
    """
    A class for the track render of the monitor app.
    """

    def __init__(self):
        super().__init__(title="Racetrack View", width=500, height=500)

    def init_ui(self):
        pass

    def closeEvent(self, event):
        event.accept()


class SerialView(Window):
    """
    A class for the serial IO viewer of the monitor app.
    """

    def __init__(self):
        super().__init__(title="Serial IO View", width=500, height=500)

    def init_ui(self):
        pass

    def closeEvent(self, event):
        event.accept()


class BatteryCurrentPlot(FigureCanvas):
    """
    A class that encompasses a line graph with many plotted points.
    """

    def __init__(self,
                 parent=None,
                 max_current: int = 100,
                 min_current: int = -100,
                 width: int = 32, height: int = 18,
                 subplot_rows: int = 1,
                 subplot_columns: int = 1,
                 dpi=60
                 ):
        """

        :param parent:
            The parent widget of the plot_data.
        :param max_current:
            The max current draw the battery could experience.
        :param min_current:
            The max negative current draw the battery could experience.
        :param width:
            The width of the plot_data in inches.
        :param height:
            The height of the plot_data in inches.
        :param subplot_rows:
            The number of rows, where subplots could be placed.
        :param subplot_columns:
            The number of columns, where subplots could be placed.
        :param dpi:
            The DPI of the plot_data.
        """
        self.figure = Figure(figsize=(width, height), dpi=dpi)  # creates the figure object
        FigureCanvas.__init__(self, self.figure)

        self.subplot_rows: int = subplot_rows
        self.subplot_columns: int = subplot_columns

        self.setParent(parent)  # sets the parent widget

        FigureCanvas.setSizePolicy(self, QSizePolicy.Expanding, QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)

    def plot_data(self,
                  points: List[Tuple[int, datetime]],
                  line_type: str = "r-",
                  line_width: float = 1,
                  batch_size: int = 1
                  ):
        axes = self.figure.add_subplot(self.subplot_rows, self.subplot_columns, 1)
        axes.set_title('Battery Current Draw')
        axes.plot(
            BatteryCurrentPlot.order_points(points, batch_size),
            line_type,
            linewidth=line_width
        )  # plots all the data as a line
        self.draw()

    @staticmethod
    def order_points(points_to_order: List[Tuple[int, datetime]], sublist_item_count: int = 1) -> List[int]:
        """
        Orders the given points based on their datetime. Should the datetime be identical,
        leaves the items in their current order.
        """
        averaged_list: List = []
        for tuple_batch in batch(points_to_order, sublist_item_count):  # averages out currents
            avg_value: int = sum([tup[0] for tup in tuple_batch]) / sublist_item_count  # averages the current in batch
            avg_date: datetime = datetime.min

            counter: int = 0
            for tup in tuple_batch:  # gets the middle date in batch
                if counter == sublist_item_count // 2:
                    avg_date = tup[1]
                    break
                counter += 1

            averaged_list.append((avg_value, avg_date))

        averaged_list.sort(key=lambda point: point[1])
        sorted_points: List[int] = [averaged_list[i][0] for i in range(len(averaged_list))]
        return sorted_points
