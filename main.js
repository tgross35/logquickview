// main.js
// This file should create windows and handle all system events

const {app, BrowserWindow, Menu} = require('electron')
const url = require('url')
const path = require('path')
const {ipcMain, dialog} = require('electron')

// var debug = false

const isMac = process.platform === 'darwin'
let win

// const { dialog } = require('electron')
// const selectLogfiles = dialog.showOpenDialog(null, {
//     properties: ['openFile', 'multiSelections'],
//     filters:[
//     {name:'Log', extentions:['csv', 'log']}
//     ]}, (filePaths))

const menuTemplate = [
  // { role: 'appMenu' }
  ...(isMac ? [{
    label: app.name,
    submenu: [
      { role: 'about' },
      { type: 'separator' },
      { role: 'services' },
      { type: 'separator' },
      { role: 'hide' },
      { role: 'hideothers' },
      { role: 'unhide' },
      { type: 'separator' },
      { role: 'quit' }
    ]
  }] : []),
  // { role: 'fileMenu' }
  {
    label: 'File',
    submenu: [
        {label:'Open', click() {openLogFileDialog()}},
        isMac ? { role: 'close' } : { role: 'quit' }
    ]
  },
  // { role: 'editMenu' }
  {
    label: 'Edit',
    submenu: [
      { role: 'undo' },
      { role: 'redo' },
      { type: 'separator' },
      { role: 'cut' },
      { role: 'copy' },
      { role: 'paste' },
      ...(isMac ? [
        { role: 'pasteAndMatchStyle' },
        { role: 'delete' },
        { role: 'selectAll' },
        { type: 'separator' },
        {
          label: 'Speech',
          submenu: [
            { role: 'startspeaking' },
            { role: 'stopspeaking' }
          ]
        }
      ] : [
        { role: 'delete' },
        { type: 'separator' },
        { role: 'selectAll' }
      ])
    ]
  },
  // { role: 'viewMenu' }
  {
    label: 'View',
    submenu: [
      { role: 'reload' },
      { role: 'forcereload' },
      { role: 'toggledevtools' },
      { type: 'separator' },
      { role: 'resetzoom' },
      { role: 'zoomin' },
      { role: 'zoomout' },
      { type: 'separator' },
      { role: 'togglefullscreen' }
    ]
  },
  // { role: 'windowMenu' }
  {
    label: 'Window',
    submenu: [
      { role: 'minimize' },
      { role: 'zoom' },
      ...(isMac ? [
        { type: 'separator' },
        { role: 'front' },
        { type: 'separator' },
        { role: 'window' }
      ] : [
        { role: 'close' }
      ])
    ]
  },
  {
    role: 'help',
    submenu: [
      {
        label: 'Learn More',
        click: async () => {
          const { shell } = require('electron')
          await shell.openExternal('https://electronjs.org')
        }
      }
    ]
  }
]

const menu = Menu.buildFromTemplate(menuTemplate)
const { ipcRenderer } = require('electron');

ipcMain.on('open-log-file-dialog', (event, path) => {
    console.log(path);
    openLogFileDialog();
})

function openLogFileDialog() {
    const fs = require('fs');
    console.log('test1234');
    let openFPs = dialog.showOpenDialog({properties: ['openFile']}).then(fileNames=> {
        console.log(fileNames);
        var path = fileNames.filePaths[0]

        // TODO: make guesses about mail.log, access.log, etc based on file path
        // fileNames is an array that contains all the selected
        if (path === undefined) {
            console.log("No file selected");
        } else {readFile(path);}
    });

  function readFile(filepath) {
      console.log('Reading file');
      fs.readFile(filepath, 'utf-8', (err, data) => {
          if (err) {
              alert("An error ocurred reading the file :" + err.message)
              return
          }

          // handle the file content
          win.webContents.send('fileData', data);
      })
  }
}

function createWindow () {
  // Create the browser window.
  win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      nodeIntegration: true
    }
  })

  Menu.setApplicationMenu(menu)

  // and load the index.html of the app.
  win.loadFile('index.html')

  // Open the DevTools.
  win.webContents.openDevTools()
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.whenReady().then(createWindow)

// Quit when all windows are closed.
app.on('window-all-closed', () => {
  // On macOS it is common for applications and their menu bar
  // to stay active until the user quits explicitly with Cmd + Q
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  // On macOS it's common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow()
  }
})

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and require them here.
