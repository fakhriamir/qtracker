import QtQuick 1.0
import "../Components"

OptionPage {
    id: root
    title: "Map"
    options: mapmodel
    property string currentmap: ""

    signal mapSelected(int index, string baseName, string fileName)

    Settings { id: settings }

    RefpointSelectionPage { id: calselectpage }
    MapSelectionPage {
        id: mapselectpage;
        onMapSelected: {
            mapname.value = baseName
            root.currentmap = baseName
            root.mapSelected(index,baseName,fileName)
            pageStack.pop()
        }
    }

    VisualItemModel {
        id: mapmodel

        OptionList {
            id: edit
            title: "Options"
            items: optionitems

            DynamicItemModel {
                id: optionitems
                name: "optionitems"
                OptionInputItem  { id: mapname;   text: "Map";          value:"no map"; button: true; onClicked: pageStack.push(mapselectpage) }
                OptionInputItem  { id: refpoints; text: "Calibration";  value:"";       button: true; onClicked: pageStack.push(calselectpage) }
                OptionInputItem  { id: datum;     text: "Datum";        value:"Wgs84";  button: true; }
            }

            function base(filename) {
                var txt = String(filename);
                var p1 = txt.lastIndexOf('/');
                var p2 = txt.lastIndexOf('.');
                return txt.slice(p1+1,p2);
            }

            Component.onCompleted: {
                console.log("mapeditpage.edit.onCompleted",settings.database, settings.table, settings.filter)
                var filename = settings.getProperty("map_filename","")
                if (filename == "") {
                    mapname.value = "no map"
                } else {
                    currentmap = base(filename)
                    mapname.value = currentmap
                }
                console.log("mapeditpage.edit.onCompleted:",mapname.value)
            }

        }
/*
        OptionList {
            id: editrefpoint
            title: "Calibration Points"
            items: refpoints

            DynamicItemModel {
                id: refpoints
                name: "securityitems"
                OptionTextItem  { id: newrefpoint; text: "<new calibration point>"; button: true; onClicked: pageStack.push(calselectpage) }
            }
        }
*/
    }
    onVisibleChanged: {
        if ((visible==true) && (currentmap=="")) pageStack.push(mapselectpage);
    }
}
