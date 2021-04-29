var component;
var sprite;
var object_parent;

function destroyAppActivityIndicator(){
    object_parent.enabled = true
    sprite.destroy()
    component.destroy()

}
function createAppActivityIndicator(_parent) {
    object_parent = _parent
    component = Qt.createComponent("qrc:/AppActivityIndicator.qml");
    if (component.status == Component.Ready)
        finishCreation();
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation() {
    if (component.status == Component.Ready) {
        sprite = component.createObject(object_parent);
        object_parent.enabled = false
        if (sprite == null) {
            // Error Handling
            console.log("Error creating object");
        }
    } else if (component.status == Component.Error) {
        // Error Handling
        console.log("Error loading component:", component.errorString());
    }
}
