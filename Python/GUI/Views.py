from Python.Utils.GUI import App, Window
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QAction, qApp
import sys


class MonitorApp(App):
    def show_window(self):
        _ = MainView()
        sys.exit(self.exec_())


class MainView(Window):
    """
    A class for the start screen of the monitor app
    """

    def init_ui(self):
        """ Lays out and shows the main window of the app. """
        exit_act = QAction(QIcon('exit.png'), '&Exit', self)
        exit_act.setShortcut('Ctrl+Q')
        exit_act.setStatusTip('Exit application')
        exit_act.triggered.connect(qApp.quit)

        self.statusBar()

        menubar = self.menuBar()
        file_menu = menubar.addMenu('&File')
        file_menu.addAction(exit_act)

        self.show()


class BatteryView(Window):
    """
    A class for the batter view of the monitor app
    """


class LocationView(Window):
    """
    A class for the track render of the monitor app
    """


class SerialViewer(Window):
    """
    A class for the serial IO viewer of the monitor app
    """
