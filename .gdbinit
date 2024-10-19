set sysroot /
target remote :5555

trace widgets/widgets/qmdiarea.cpp:1371
actions
    collect $args
    collect *this
#    collect indicesToActivatedChildren
#    collect childWindows
    collect *indicesToActivatedChildren.d.ptr@3
    collect *childWindows.d.ptr@3
end

set default-collect *this

#trace src/Gui/View.cpp:58
#actions
#collect this
## collect $args
## collect $locals 
#end

tstart

b exit

b QMdiAreaPrivate::_q_moveTab
b QMdiAreaPrivate::appendChild
b QMdiAreaPrivate::emitWindowActivated
b QMdiAreaPrivate::updateActiveWindow
b QMdiArea::removeSubWindow
b QMdiArea::viewportEvent



#b src/Mod/Sketcher/App/SketchObject.cpp:10006
#b src/Gui/MainWindow.cpp:removeWindow
#b /usr/src/debug/qt6-base/qtbase/src/widgets/widgets/qmdiarea.cpp:1371
#b /usr/src/debug/qt6-base/qtbase/src/widgets/widgets/qtabbar.cpp:772

# Start the program in gdbserver
continue
#
##set logging overwrite on
#
tstop
tfind start

set $i = 1

while ($trace_frame != -1)
    eval "set logging file gdb-%d.txt", $i
    set logging enabled on
    printf "Frame %d %s:\n", $trace_frame, $trace_func
    tdump
    set logging enabled off
    set $i = $i + 1
    tfind
end
