from PyQt5.QtWidgets import QApplication, QMainWindow, QMessageBox, QPushButton, QSizePolicy
from PyQt5.QtGui import QIcon
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import random
import sys
import threading


class App(QApplication):
    """
    A class encompassing a basic PyQt application.
    Creates a default window and starts a separate GUI thread.
    Override show_window to create a different start window.
    """
    def __init__(self):
        super().__init__(sys.argv)
        self.setStyle("Windows")
        threading.Thread(name="Monitor GUI Thread", target=self.show_window).run()

    def show_window(self):
        _ = Window()
        sys.exit(self.exec_())


class Window(QMainWindow):
    """
    A class encompassing a basic PyQt window.
    The init_ui method should be overridden to produce different layouts.
    """
    def __init__(self,
                 title: str = "Greenpower Monitor App",
                 icon: QIcon = QIcon("Icon.jpg"),
                 width: int = 1200,
                 height: int = 800,
                 *args, **kwargs
                 ):
        super().__init__(*args, **kwargs)
        self.setWindowTitle(title)
        self.setWindowIcon(icon)
        self.resize(width, height)
        self.init_ui()

    def init_ui(self):
        """ The method called to set the layout of the window. """
        # dummy implementation
        self.show()

    def closeEvent(self, event):
        """ The method invoked when a PyQt window should be closed. """
        # close any used serial port

        confirmation = QMessageBox.question(self,
                                            'Quit Confirmation',
                                            "Are you sure to quit the monitor?",
                                            QMessageBox.Yes | QMessageBox.No,
                                            QMessageBox.No
                                            )

        if confirmation == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()


def run_app():
    _ = App()


if __name__ == '__main__':
    run_app()
