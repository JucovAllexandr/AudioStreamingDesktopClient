import QtQuick 2.15

Item {
    property alias hidenText: hidenText.text
    property alias text: textInput.text
    property alias echoMode: textInput.echoMode
    id: root
    focus: false

    Rectangle{
        id: background
        anchors.fill: root
        radius: 20
        focus: false
        color: "#A4A4A4"

        Text{
            id:hidenText
            anchors.fill: background
            anchors.leftMargin: 15
            font.pixelSize: root.height-5
            focus: false
            text: ""
            color: "#DBDBDB"
        }

        TextInput {
            id: textInput
            anchors.leftMargin: 15
            anchors.rightMargin: 15
            anchors.fill: background
            clip: true
            color: "white"
            focus: true
            selectByMouse: true
            selectionColor: "#18A0FB"
            font.pixelSize: root.height-5

            onTextChanged: {
                if(textInput.text != ""){
                    hidenText.visible = false
                }
                else{
                    hidenText.visible = true
                }
            }

            onActiveFocusChanged: {
                if(textInput.activeFocus == true){
                    background.border.color = "#18A0FB"
                    background.border.width = 2
                }else{
                    background.border.width = 0
                }
            }
        }
    }
}
