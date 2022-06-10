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
    signal qmlSignal1()
    signal qmlSignalPrint()
    property string source // for main.cpp
    property real scaleStep: Math.sqrt(2)
    property int page_mode: 0
    property int page_no: 0

    function goSearch(search_string: string, search_index: int)
    {
        searchField.text = search_string
        view.searchModel.currentResult = search_index
    }

    function goPage(page: int)
    {
        view.goToPage(page)
        page_no = view.currentPage
//        root.qmlSignal(view.currentPage)
    }

    function goPrev()
    {
        if(view.currentPage > 0)
        {
            view.goToPage(view.currentPage - 1)
            page_no = view.currentPage
            root.qmlSignal(view.currentPage)
        }
    }

    function goNext()
    {
        if(view.currentPage < doc.pageCount - 1)
        {
            view.goToPage(view.currentPage + 1)
            page_no = view.currentPage
            root.qmlSignal(view.currentPage)
        }
    }

    function fitPage()
    {
        page_mode = 2
        view.scaleToPage(root.width, root.height)
    }

    function resizeArea()
    {
//        if(page_mode == 1)
//        {
//            view.scaleToWidth(root.width, root.height)
//        }
//        else if(page_mode == 2)
//        {
//            view.scaleToPage(root.width, root.height)
//        }
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
            id: view
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
                        enabled: view.renderScale < 10
                        icon.source: "qrc:/BDLS/icons/zoom-in.svg"
                        onTriggered: {
                            page_mode = 0
                            view.renderScale *= root.scaleStep
                        }
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 1000
                    ToolTip.text: "zoom in"
                }
                ToolButton {
                    action: Action {
                        shortcut: StandardKey.ZoomOut
                        enabled: view.renderScale > 0.1
                        icon.source: "qrc:/BDLS/icons/zoom-out.svg"
                        onTriggered: {
                            page_mode = 0
                            view.renderScale /= root.scaleStep
                        }
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 1000
                    ToolTip.text: "zoom out"
                }
                ToolButton {
                    action: Action {
                        icon.source: "qrc:/BDLS/icons/zoom-fit-width.svg"
                        onTriggered: {
                            page_mode = 1
                            view.scaleToWidth(root.width, root.height)
                        }
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 1000
                    ToolTip.text: "zoom fit width"
                }
                ToolButton {
                    action: Action {
                        icon.source: "qrc:/BDLS/icons/zoom-fit-best.svg"
                        onTriggered: {
                            page_mode = 2
                            view.scaleToPage(root.width, root.height)
                        }
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 1000
                    ToolTip.text: "zoom fit page"
                }
                ToolButton {
                    action: Action {
                        shortcut: "Ctrl+0"
                        icon.source: "qrc:/BDLS/icons/zoom-original.svg"
                        onTriggered: {
                            page_mode = 0
                            view.resetScale()
                        }
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 1000
                    ToolTip.text: "zoom original"
                }
                ToolButton {
                    action: Action {
                        shortcut: "Ctrl+L"
                        icon.source: "qrc:/BDLS/icons/rotate-left.svg"
                        onTriggered: view.pageRotation -= 90
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 1000
                    ToolTip.text: "rotate left"
                }
                ToolButton {
                    action: Action {
                        shortcut: "Ctrl+R"
                        icon.source: "qrc:/BDLS/icons/rotate-right.svg"
                        onTriggered: view.pageRotation += 90
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 1000
                    ToolTip.text: "rotate right"
                }
                ToolButton {
                    action: Action {
                        icon.source: "qrc:/BDLS/icons/go-previous-view-page.svg"
                        enabled: view.currentPage > 0
                        onTriggered: {
                            view.goToPage(view.currentPage - 1)
                            page_no = view.currentPage
                            root.qmlSignal(view.currentPage)
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
                    value: view.currentPage + 1
                    onValueModified: {
                        view.goToPage(value - 1)
                        page_no = view.currentPage
                        root.qmlSignal(view.currentPage)
                    }
                    Shortcut {
                        sequence: StandardKey.MoveToPreviousPage
                        onActivated:{
                            view.goToPage(currentPageSB.value - 2)
                            page_no = view.currentPage
                            root.qmlSignal(view.currentPage)
                        }
                    }
                    Shortcut {
                        sequence: StandardKey.MoveToNextPage
                        onActivated: {
                            view.goToPage(currentPageSB.value)
                            page_no = view.currentPage
                            root.qmlSignal(view.currentPage)
                        }
                    }
                }
                ToolButton {
                    action: Action {
                        icon.source: "qrc:/BDLS/icons/go-next-view-page.svg"
                        enabled: view.currentPage < doc.pageCount - 1
                        onTriggered: {
                            view.goToPage(view.currentPage + 1)
                            page_no = view.currentPage
                            root.qmlSignal(view.currentPage)
                        }

                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 2000
                    ToolTip.text: "go forward"
                }
                ToolButton {
                    action: Action {
                        icon.source: "qrc:/BDLS/icons/edit-copy.svg"
                        onTriggered: root.qmlSignal1()
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 1000
                    ToolTip.text: "view single page"
                }
                ToolButton {
                    action: Action {
                        icon.source: "qrc:/BDLS/icons/printer-24.png"
                        onTriggered: root.qmlSignalPrint()
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 1000
                    ToolTip.text: "print"
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

    Drawer {
        id: searchDrawer
        edge: Qt.LeftEdge
        modal: false
        width: 300
        y: root.header.height
        height: view.height
        dim: false
        clip: true

        TabBar {
            id: sidebarTabs
            x: -width
            rotation: -90
            transformOrigin: Item.TopRight
            currentIndex: 3 // bookmarks by default
            TabButton {
                text: qsTr("Info")
            }
            TabButton {
                text: qsTr("Search Results")
            }
            TabButton {
                text: qsTr("Bookmarks")
            }
            TabButton {
                text: qsTr("Pages")
            }
        }

        GroupBox {
            anchors.fill: parent
            anchors.leftMargin: sidebarTabs.height

            StackLayout {
                anchors.fill: parent
                currentIndex: sidebarTabs.currentIndex
                component InfoField: TextInput {
                    width: parent.width
                    selectByMouse: true
                    readOnly: true
                    wrapMode: Text.WordWrap
                }
                Column {
                    spacing: 6
                    width: parent.width - 6
                    Label { font.bold: true; text: qsTr("Title") }
                    InfoField { text: doc.title }
                    Label { font.bold: true; text: qsTr("Author") }
                    InfoField { text: doc.author }
                    Label { font.bold: true; text: qsTr("Subject") }
                    InfoField { text: doc.subject }
                    Label { font.bold: true; text: qsTr("Keywords") }
                    InfoField { text: doc.keywords }
                    Label { font.bold: true; text: qsTr("Producer") }
                    InfoField { text: doc.producer }
                    Label { font.bold: true; text: qsTr("Creator") }
                    InfoField { text: doc.creator }
                    Label { font.bold: true; text: qsTr("Creation date") }
                    InfoField { text: doc.creationDate }
                    Label { font.bold: true; text: qsTr("Modification date") }
                    InfoField { text: doc.modificationDate }
                }
                ListView {
                    id: searchResultsList
                    implicitHeight: parent.height
                    model: view.searchModel
                    ScrollBar.vertical: ScrollBar { }
                    delegate: ItemDelegate {
                        id: resultDelegate
                        required property int index
                        required property int page
                        required property int indexOnPage
                        required property point location
                        required property string contextBefore
                        required property string contextAfter
                        width: parent ? parent.width : 0
                        RowLayout {
                            anchors.fill: parent
                            spacing: 0
                            Label {
                                text: "Page " + (resultDelegate.page + 1) + ": "
                            }
                            Label {
                                text: resultDelegate.contextBefore
                                elide: Text.ElideLeft
                                horizontalAlignment: Text.AlignRight
                                Layout.fillWidth: true
                                Layout.preferredWidth: parent.width / 2
                            }
                            Label {
                                font.bold: true
                                text: view.searchString
                                width: implicitWidth
                            }
                            Label {
                                text: resultDelegate.contextAfter
                                elide: Text.ElideRight
                                Layout.fillWidth: true
                                Layout.preferredWidth: parent.width / 2
                            }
                        }
                        highlighted: ListView.isCurrentItem
                        onClicked: {
                            searchResultsList.currentIndex = resultDelegate.index
                            view.goToLocation(resultDelegate.page, resultDelegate.location, 0)
                            view.searchModel.currentResult = resultDelegate.indexOnPage
                        }
                    }
                }
                TreeView {
                    id: bookmarksTree
                    implicitHeight: parent.height
                    implicitWidth: parent.width
                    columnWidthProvider: function() { return width }
                    delegate: TreeViewDelegate {
                        required property int page
                        required property point location
                        required property real zoom
                        onClicked: view.goToLocation(page, location, zoom)
                    }
                    model: PdfBookmarkModel {
                        document: doc
                    }
                    ScrollBar.vertical: ScrollBar { }
                }
                GridView {
                    id: thumbnailsView
                    implicitWidth: parent.width
                    implicitHeight: parent.height
                    model: doc.pageCount
                    cellWidth: width / 2
                    cellHeight: cellWidth + 10
                    delegate: Item {
                        required property int index
                        width: thumbnailsView.cellWidth
                        height: thumbnailsView.cellHeight
                        Rectangle {
                            id: paper
                            width: image.width
                            height: image.height
                            x: (parent.width - width) / 2
                            y: (parent.height - height - pageNumber.height) / 2
                            PdfPageImage {
                                id: image
                                document: doc
                                currentPage: index
                                asynchronous: true
                                fillMode: Image.PreserveAspectFit
                                property size naturalSize: doc.pagePointSize(index)
                                property bool landscape: naturalSize.width > naturalSize.height
                                width: landscape ? thumbnailsView.cellWidth - 6
                                                 : height * naturalSize.width / naturalSize.height
                                height: landscape ? width * naturalSize.height / naturalSize.width
                                                  : thumbnailsView.cellHeight - 14
                                sourceSize.width: width
                                sourceSize.height: height
                            }
                        }
                        Text {
                            id: pageNumber
                            anchors.bottom: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Page " + (image.currentFrame + 1)
                        }
                        TapHandler {
                            onTapped: {
                                view.goToPage(index)
                                page_no = view.currentPage
                                root.qmlSignal(view.currentPage)
                            }
                        }
                    }
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
                        icon.source: "qrc:/BDLS/icons/document-open.svg"
                        onTriggered: searchDrawer.open()
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 1000
                    ToolTip.text: "info"
                }
                ToolButton {
                    action: Action {
                        icon.source: "qrc:/BDLS/icons/go-up-search.svg"
                        shortcut: StandardKey.FindPrevious
                        onTriggered: view.searchBack()
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 1000
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
                        onTriggered: view.searchForward()
                    }
                    ToolTip.visible: enabled && hovered
                    ToolTip.delay: 1000
                    ToolTip.text: "find next"
                }
                Label {
                    Layout.fillWidth: true
                    property size implicitPointSize: doc.pagePointSize(view.currentPage)
                    text: "page " + (view.currentPage + 1) + " of " + doc.pageCount +
                          " scale " + view.renderScale.toFixed(2) +
                          " original " + implicitPointSize.width.toFixed(1) + "x" + implicitPointSize.height.toFixed(1) + "pts"
                    visible: doc.status === PdfDocument.Ready
                }
            }
        }
}
