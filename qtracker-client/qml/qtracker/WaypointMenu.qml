import QtQuick 1.0

Page {
    id: root

    function confirm() {
        pageStack.pop();
    }
    function cancel() {
        pageStack.pop();
    }
/*
    WaypointEdit {
        id: edit
    }
*/
    function newentry() {
        //pageStack.push(edit)
    }

    MenuEntry {
        id: heading
        x: 2; y: 2
        width: parent.width
        height: 54
        text: "Waypoint Menu"
        leftButtonVisible: true
        onLeftClicked: root.cancel();
    }

    MenuEntry {
        id: start
        anchors.top: heading.bottom
        width: parent.width
        height: 54
        text: "New Waypoint"
        rightButtonVisible: true
        onRightClicked: root.newentry();
    }

    MenuEntry {
        id: list
        anchors.top: start.bottom
        anchors.bottom: parent.bottom
        width: parent.width
/*
        WaypointList {
            id: listbox
            anchors.fill: parent
        }
*/
    }
}

/*
New
=================
Name:
Position:
Altitude:
Time:
| save | cancel |

List
=================
d e s <name>
| cancel |
*/