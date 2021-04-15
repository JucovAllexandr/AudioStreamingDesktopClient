import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Loader{
        id: pageLoader
        anchors.fill: parent
        visible: source != ""
        state: Auth.authenticated? "Authorized" : "NotAuthorized"

        states: [
                State {
                    name: "Authorized"
                    PropertyChanges {
                        target: pageLoader;
                        source: "qrc:/app.qml"
                    }
                },
                State {
                    name: "NotAuthorized"
                    PropertyChanges {
                        target: pageLoader;
                        source: "qrc:/login.qml"
                    }

                }
            ]
    }

}
