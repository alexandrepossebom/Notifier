# For QT notifier you need get sources (or binary) package in :
# http://possebom.com/weechat
#
# 2009-08-25, Alexandre Possebom <alexandre.possebom@gmail.com>:
#   First Release

import weechat, os, dbus

weechat.register("notifier", "Alexandre Possebom", "0.1", "GPL", "notifier: dbus and tray icon notification system for weechat", "", "")

weechat.hook_signal("weechat_pv", "dbus_new", "")
weechat.hook_signal("weechat_highlight", "dbus_new", "")
weechat.hook_signal("key_pressed", "dbus_nonew", "")

isnew = False
bus = dbus.SessionBus()
notifier = bus.get_object("org.notifier.Launcher", "/Interface")

def dbus_nonew( data, signal, message ):
    global isnew
    if isnew:
        isnew = False
        notifier.nonewMsg()
    return weechat.WEECHAT_RC_OK
def dbus_new( data, signal, message ):
    global isnew
    isnew = True
    notifier.newMsg()
    return weechat.WEECHAT_RC_OK

# vim: ai ts=4 sts=4 et sw=4
