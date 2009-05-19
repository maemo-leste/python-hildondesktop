
import gtk
import hildondesktop

class MyPlugin(hildondesktop.HomeItem):

    __gtype_name__ = 'MyPlugin'

    def __init__(self):
        hildondesktop.HomeItem.__init__(self)

        self.button = gtk.Button(label="Hello, World!")
        self.button.show()
        self.set_resize_type(hildondesktop.HD_HOME_PLUGIN_ITEM_RESIZE_BOTH)
        self.add(self.button)

plugin = None

def hd_plugin_get_objects():
    global plugin
    plugin = MyPlugin()
    return [plugin]

if __name__ == '__main__':
    a = hd_plugin_get_objects()
    a[0].show_all()

    gtk.main()
