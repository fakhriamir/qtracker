import QtQuick 1.0
import QtMobility.publishsubscribe 1.1
import "../Components"

OptionPage {
    id: root
    title: "Track"
    options: trkoptions

    function confirm() {
        pageStack.pop();
    }
    function cancel() {
        pageStack.pop();
    }

    ValueSpaceSubscriber  {
        id: trackstatus;
        path: "/server/track/status"
        property string status: value
        onStatusChanged: console.log("TrackMenu.trackstatus:onStatusChanged: ", status)
        Component.onCompleted: console.log("TrackMenu.trackstatus:onCompleted: ", value)
    }

    ValueSpaceSubscriber  {
        id: trackname;
        path: "/server/track/name"
    }

    VisualItemModel {
        id: trkoptions

        OptionList {
            id: startstop
            title: "Recording"
            items: recordingitems

            DynamicItemModel {
                id: recordingitems
                name: "recordingitems"

                OptionTextItem { text: trackstatus.status=="idle"? "Start Track": "Stop Track" }
            }
        }

        TrackList {
            id: lst
            title: "List"
        }
    }
}