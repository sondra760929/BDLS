/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Pdf

Rectangle {
    id: root
//    width: 800
//    height: 1024
    color: "lightgrey"
//    title: document.title
    visible: true
    signal qmlSignal(int page_no)
    property string source // for main.cpp
    property real scaleStep: Math.sqrt(2)
    property int page_mode: 0
    property int page_no: 0
    property int current_view: 0

    property var view:[view1, view2]

    function goPage(page: int)
    {
        view[current_view].goToPage(page)
        page_no = view[current_view].currentPage
//        root.qmlSignal(view[current_view].currentPage)
    }

    function resizeArea()
    {
//        if(page_mode == 1)
//        {
//            view[current_view].scaleToWidth(root.width, root.height)
//        }
//        else if(page_mode == 2)
//        {
//            view[current_view].scaleToPage(root.width, root.height)
//        }
    }

    function changeViewer()
    {
        if(current_view == 0)
        {
            current_view = 1;
            view[1].visible = true
            view[0].visible = false
        }
        else
        {
            current_view = 0;
            view[0].visible = true
            view[1].visible = false
        }
    }
        ToolBar {
            id: toolbar
            anchors.top: parent.top;
            anchors.left: parent.left
            anchors.right: parent.right
            RowLayout {
                anchors.fill: parent
                anchors.rightMargin: 6
//                ToolButton {
//                    action: Action {
//                        shortcut: StandardKey.Open
//                        icon.source: "qrc:/BDLS/icons/document-open.svg"
//                        onTriggered: fileDialog.open()
//                    }
//                }
                ToolButton {
                    action: Action {
                        shortcut: StandardKey.ZoomIn
                        enabled: view[current_view].renderScale < 10
                        icon.source: "qrc:/BDLS/icons/zoom-in.svg"
                        onTriggered: {
                            page_mode = 0
                            view[current_view].renderScale *= root.scaleStep
                        }
                    }
                }
                ToolButton {
                    action: Action {
                        shortcut: StandardKey.ZoomOut
                        enabled: view[current_view].renderScale > 0.1
                        icon.source: "qrc:/BDLS/icons/zoom-out.svg"
                        onTriggered: {
                            page_mode = 0
                            view[current_view].renderScale /= root.scaleStep
                        }
                    }
                }
                ToolButton {
                    action: Action {
                        icon.source: "qrc:/BDLS/icons/zoom-fit-width.svg"
                        onTriggered: {
                            page_mode = 1
                            view[current_view].scaleToWidth(root.width, root.height)
                        }
                    }
                }
                ToolButton {
                    action: Action {
                        icon.source: "qrc:/BDLS/icons/zoom-fit-best.svg"
                        onTriggered: {
                            page_mode = 2
                            view[current_view].scaleToPage(root.width, root.height)
                        }
                    }
                }
                ToolButton {
                    action: Action {
                        shortcut: "Ctrl+0"
                        icon.source: "qrc:/BDLS/icons/zoom-original.svg"
                        onTriggered: {
                            page_mode = 0
                            view[current_view].resetScale()
                        }
                    }
                }
                ToolButton {
                    action: Action {
                        shortcut: "Ctrl+L"
                        icon.source: "qrc:/BDLS/icons/rotate-left.svg"
                        onTriggered: view[current_view].pageRotation -= 90
                    }
                }
                ToolButton {
                    action: Action {
                        shortcut: "Ctrl+R"
                        icon.source: "qrc:/BDLS/icons/rotate-right.svg"
                        onTriggered: view[current_view].pageRotation += 90
                    }
                }
                ToolButton {
                    action: Action {
                        icon.source: "qrc:/BDLS/icons/go-previous-view-page.svg"
                        enabled: view[current_view].backEnabled
                        onTriggered: {
                            view[current_view].back()
                            page_no = view[current_view].currentPage
                            root.qmlSignal(view[current_view].currentPage)
                        }
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 2000
                    ToolTip.text: "go back"
                }
                SpinBox {
                    id: currentPageSB
                    from: 1
                    to: doc.pageCount
                    editable: true
                    Layout.fillWidth: true
                    value: view[current_view].currentPage + 1
                    onValueModified: {
                        view[current_view].goToPage(value - 1)
                        page_no = view[current_view].currentPage
                        root.qmlSignal(view[current_view].currentPage)
                    }
                    Shortcut {
                        sequence: StandardKey.MoveToPreviousPage
                        onActivated: view[current_view].goToPage(currentPageSB.value - 2)
                    }
                    Shortcut {
                        sequence: StandardKey.MoveToNextPage
                        onActivated: view[current_view].goToPage(currentPageSB.value)
                    }
                }
                ToolButton {
                    action: Action {
                        icon.source: "qrc:/BDLS/icons/go-next-view-page.svg"
                        enabled: view[current_view].forwardEnabled
                        onTriggered: {
                            view[current_view].forward()
                            page_no = view[current_view].currentPage
                            root.qmlSignal(view[current_view].currentPage)
                        }

                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 2000
                    ToolTip.text: "go forward"
                }
                ToolButton {
                    action: Action {
                        shortcut: StandardKey.SelectAll
                        icon.source: "qrc:/BDLS/icons/edit-select-all.svg"
                        onTriggered: view[current_view].selectAll()
                    }
                }
                ToolButton {
                    action: Action {
                        shortcut: StandardKey.Copy
                        icon.source: "qrc:/BDLS/icons/edit-copy.svg"
                        onTriggered: changeViewer()
                    }
                }
                Shortcut {
                    sequence: StandardKey.Find
                    onActivated: searchField.forceActiveFocus()
                }
                Shortcut {
                    sequence: StandardKey.Quit
                    onActivated: Qt.quit()
                }
            }
        }

        FileDialog {
            id: fileDialog
            title: "Open a PDF file"
            nameFilters: [ "PDF files (*.pdf)" ]
            onAccepted: doc.source = selectedFile
        }

        Dialog {
            id: passwordDialog
            title: "Password"
            standardButtons: Dialog.Ok | Dialog.Cancel
            modal: true
            closePolicy: Popup.CloseOnEscape
            anchors.centerIn: parent
            width: 300

            contentItem: TextField {
                id: passwordField
                placeholderText: qsTr("Please provide the password")
                echoMode: TextInput.Password
                width: parent.width
                onAccepted: passwordDialog.accept()
            }
            onOpened: function() { passwordField.forceActiveFocus() }
            onAccepted: doc.password = passwordField.text
        }

        Dialog {
            id: errorDialog
            title: "Error loading " + doc.source
            standardButtons: Dialog.Close
            modal: true
            closePolicy: Popup.CloseOnEscape
            anchors.centerIn: parent
            width: 300
            visible: doc.status === PdfDocument.Error

            contentItem: Label {
                id: errorField
                text: doc.error
            }
        }

        PdfDocument {
            id: doc
            source: Qt.resolvedUrl(root.source)
            onPasswordRequired: passwordDialog.open()
        }

        PdfScrollablePageView {
            id: view1
            anchors.top: toolbar.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: bottombar.top
            anchors.leftMargin: searchDrawer.position * searchDrawer.width
            document: doc
            searchString: searchField.text
            onWidthChanged: resizeArea()
            onHeightChanged: resizeArea()
        }

        PdfMultiPageView {
            id: view2
            visible: false
            anchors.top: toolbar.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: bottombar.top
            anchors.leftMargin: searchDrawer.position * searchDrawer.width
            document: doc
            searchString: searchField.text
            onWidthChanged: resizeArea()
            onHeightChanged: resizeArea()
        }

        Drawer {
            id: searchDrawer
            edge: Qt.LeftEdge
    //        modal: false
    //        dim: false // commented out as workaround for QTBUG-83859
            width: 300
            y: root.header.height
            height: view[current_view].height
            clip: true
            ListView {
                id: searchResultsList
                anchors.fill: parent
                anchors.margins: 2
                model: view[current_view].searchModel
                ScrollBar.vertical: ScrollBar { }
                delegate: ItemDelegate {
                    width: parent ? parent.width : 0
                    RowLayout {
                        anchors.fill: parent
                        spacing: 0
                        Label {
                            text: "Page " + (page + 1) + ": "
                        }
                        Label {
                            text: contextBefore
                            elide: Text.ElideLeft
                            horizontalAlignment: Text.AlignRight
                            Layout.fillWidth: true
                            Layout.preferredWidth: parent.width / 2
                        }
                        Label {
                            font.bold: true
                            text: view[current_view].searchString
                            width: implicitWidth
                        }
                        Label {
                            text: contextAfter
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                            Layout.preferredWidth: parent.width / 2
                        }
                    }
                    highlighted: Listview[current_view].isCurrentItem
                    onClicked: {
                        searchResultsList.currentIndex = index
                        view[current_view].goToLocation(page, location, 0)
                        view[current_view].searchModel.currentResult = indexOnPage
                    }
                }
            }
        }

        ToolBar {
            id: bottombar
            height: footerRow.implicitHeight
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            RowLayout {
                id: footerRow
                anchors.fill: parent
                ToolButton {
                    action: Action {
                        icon.source: "qrc:/BDLS/icons/go-up-search.svg"
                        shortcut: StandardKey.FindPrevious
                        onTriggered: view[current_view].searchBack()
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 2000
                    ToolTip.text: "find previous"
                }
                TextField {
                    id: searchField
                    placeholderText: "search"
                    Layout.minimumWidth: 150
                    Layout.maximumWidth: 300
                    Layout.fillWidth: true
                    onAccepted: searchDrawer.open()
                    Image {
                        visible: searchField.text !== ""
                        source: "qrc:/BDLS/icons/edit-clear.svg"
                        anchors {
                            right: parent.right
                            top: parent.top
                            bottom: parent.bottom
                            margins: 3
                            rightMargin: 5
                        }
                        TapHandler {
                            onTapped: searchField.clear()
                        }
                    }
                }
                ToolButton {
                    action: Action {
                        icon.source: "qrc:/BDLS/icons/go-down-search.svg"
                        shortcut: StandardKey.FindNext
                        onTriggered: view[current_view].searchForward()
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 2000
                    ToolTip.text: "find next"
                }
                Label {
                    Layout.fillWidth: true
                    property size implicitPointSize: doc.pagePointSize(view[current_view].currentPage)
                    text: "page " + (view[current_view].currentPage + 1) + " of " + doc.pageCount +
                          " scale " + view[current_view].renderScale.toFixed(2) +
                          " original " + implicitPointSize.width.toFixed(1) + "x" + implicitPointSize.height.toFixed(1) + "pts"
                    visible: doc.status === PdfDocument.Ready
                }
            }
        }
}
