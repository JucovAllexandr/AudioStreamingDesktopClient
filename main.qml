import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: root
    width: 640
    height: 480
    visible: true
    color: "#3C3C3C"
    title: qsTr("AudioStreaming")

    Connections{
        target: Auth

        function onAuthenticatedChanged(){
            console.log("onAuthenticatedChanged")

            if(Auth.authenticated){
                pageLoader.state = 'Authorized'
                pageLoader.enabled = true
            }else{
                pageLoader.state = 'NotAuthorized'
            }
            console.log(pageLoader.state)
        }
    }

    Loader{
        id: pageLoader
        anchors.fill: parent
        visible: source != ""
        state: ""

        Component.onCompleted: {
            console.log("onCompleted")

            if(Auth.authenticated){
                pageLoader.state = 'Authorized'
            }else{
                pageLoader.state = 'NotAuthorized'
            }
        }

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
