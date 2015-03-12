#include <QtGui>

#include "globj.h"
#include "mainwindow.h"

MainWindow::MainWindow()
{
  textEdit = new QTextEdit;
  
  globj = new GLobj(this);
/*
  QWidget *mainWidget = new QWidget;
  QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(globj);
    mainWidget->setLayout(mainLayout);*/
  setCentralWidget(globj);
  
  methodLabels << "A" <<  "B" << "C" << "D" << "E" << "F";
  colorRepOptions << "R" <<  "T" << "S" << "U";

  createActions();
  createMenus();
  createDockWindows();
  createStatusBar();
  setWindowTitle(tr("Assignment I3"));

}

void MainWindow::newFile()
{
  QMessageBox msgBox;
  msgBox.setText("Any changes will be lost.");
  msgBox.setInformativeText("Are you sure you wish to open a new file?");
  msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Ok);
  int ret = msgBox.exec();
  switch (ret) {
  case QMessageBox::Ok:      
    textEdit->setPlainText("");
    break;   
  case QMessageBox::Cancel:
    break;
  default:       
    break;
  }
  
}
void MainWindow::open()
{
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),".",tr("Text Files(*.txt)"));
  if (fileName.isEmpty())
    return;

  QFile myFile(fileName);
  myFile.open(QIODevice::ReadOnly);
  QTextStream textStream(&myFile);
  QString line = textStream.readAll();
  myFile.close();
  textEdit->setPlainText(line);
  statusBar()->showMessage(tr("Opened '%1'").arg(fileName), 2000);
}

void MainWindow::save()
{
  QString fileName = QFileDialog::getSaveFileName(this,
						  tr("Choose a file name"), ".",
						  tr("Text Files (*.txt)"));
  if (fileName.isEmpty())
    return;
  QFile file(fileName);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, tr("Assignment I2"),
			 tr("Cannot write file %1:\n%2.")
			 .arg(fileName)
			 .arg(file.errorString()));
    return;
  }

  QTextStream out(&file);
  QApplication::setOverrideCursor(Qt::WaitCursor);
  out << textEdit->toPlainText();
  QApplication::restoreOverrideCursor();

  statusBar()->showMessage(tr("Saved '%1'").arg(fileName), 2000);
}


void MainWindow::help()
{
  QMessageBox::about(this, tr("About Assignment I2"),
		     tr("The demo application is to incorporate file I/O and widgets"));
}

void MainWindow::createActions()
{
  newAct = new QAction(tr("&New..."), this);
  newAct->setShortcuts(QKeySequence::New);
  newAct->setStatusTip(tr("Create a blank text file"));
  connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));


  saveAct = new QAction(tr("&Save..."), this);
  saveAct->setShortcuts(QKeySequence::Save);
  saveAct->setStatusTip(tr("Save the current text file"));
  connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

  openAct = new QAction(tr("&Open..."), this);
  openAct->setShortcuts(QKeySequence::Open);
  openAct->setStatusTip(tr("Save the current text file"));
  connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

  quitAct = new QAction(tr("&Quit"), this);
  quitAct->setShortcuts(QKeySequence::Quit);
  quitAct->setStatusTip(tr("Quit the application"));
  connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

  helpAct = new QAction(tr("&Help"), this);
  helpAct->setStatusTip(tr("Show the application's help dialog"));
  connect(helpAct, SIGNAL(triggered()), this, SLOT(help()));

     
}

void MainWindow::createMenus()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(newAct);
  fileMenu->addAction(openAct);
  fileMenu->addAction(saveAct);
  fileMenu->addSeparator();
  fileMenu->addAction(quitAct);
     
  viewMenu = menuBar()->addMenu(tr("&View"));
  menuBar()->addSeparator();

  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(helpAct);
     
}

void MainWindow::createStatusBar()
{
  statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createDockWindows()
{
  QDockWidget *dock = new QDockWidget(tr("Visualization Settings"), this);
  dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
     
  QWidget *newWidget = new QWidget(this);
  createVisualSettingsGroupBox();
  newWidget->setLayout(visualSettingsLayout);
  dock->setWidget(newWidget);
 
  addDockWidget(Qt::LeftDockWidgetArea, dock);
  viewMenu->addAction(dock->toggleViewAction());


     
  dock = new QDockWidget(tr("Image Settings"), this);
  newWidget = new QWidget(this);
  createImageSettingsGroupBox();
 
 
  newWidget->setLayout(imageSettingsLayout);
  dock->setWidget(newWidget);
 
  addDockWidget(Qt::LeftDockWidgetArea, dock);
  viewMenu->addAction(dock->toggleViewAction());

}

void MainWindow::createVisualSettingsGroupBox() 
{
  visualSettingsLayout = new QVBoxLayout;
  methodGroupBox = new QGroupBox(tr("Visualization Method"));

  QVBoxLayout *methodLayout = new QVBoxLayout;
  QHBoxLayout *buttonLayout = new QHBoxLayout;
  QFormLayout *formLayout = new QFormLayout;
  
  // initialize method display widget
  methodEdit = new QLineEdit;
  methodEdit->setText(methodLabels[0]); 
  formLayout->addRow(new QLabel(tr("Current Method:")), methodEdit);
  
  QString label;
  for (int i = 0; i < NUM_BUTTONS; ++i) {
    label = "Method &";
    methodButtons[i] = new QRadioButton(label.append(methodLabels[i]), this);
    // Update the method line edit when a new radio button is selected
    connect(methodButtons[i],SIGNAL(clicked()),this,SLOT(UpdateMethodLineEdit()));
    buttonLayout->addWidget(methodButtons[i]);
  }
  // select the first method by default
  methodButtons[0]->setChecked(true);
  
  methodLayout->addLayout(buttonLayout);
  methodLayout->addLayout(formLayout);
  
  methodGroupBox->setLayout(methodLayout);


  colorGroupBox = new QGroupBox(tr("Color Representation"));
  QFormLayout *colorLayout = new QFormLayout;  
  
  colorRepComboBox = new QComboBox;
  colorRepTabBar = new QTabBar;
  
  // Change the selected tab for our display upon a new combo box option being selected
  connect(colorRepComboBox,SIGNAL(activated(QString)),this,SLOT(UpdateColorTabBar()));
  
  QListIterator<QString> i(colorRepOptions);
  int indexCount = 0;  
  // Loop through possible representation options creating a select option and tab for value
  while (i.hasNext()) {
    QString currentOption = i.next();
    colorRepComboBox->addItem(currentOption);
    colorRepTabBar->addTab(currentOption);
    colorRepTabBar->setTabEnabled(indexCount, false);
    indexCount++;
  }  
  
  colorLayout->addRow(new QLabel(tr("Color Representation:")), colorRepComboBox);
  colorLayout->addRow(new QLabel(tr("Current Setting:")), colorRepTabBar);
  colorGroupBox->setLayout(colorLayout);

  landscapeGroupBox = new QGroupBox(tr("Orientation"));
  QFormLayout *landscapeLayout = new QFormLayout;
  buttonLayout = new QHBoxLayout;
  QHBoxLayout *checkBoxLayout = new QHBoxLayout;
  portraitBtn = new QPushButton("&Portrait", this);
  landscapeBtn = new QPushButton("&Landscape", this);
  portraitCheckBox = new QCheckBox("Portrait");
  landscapeCheckBox = new QCheckBox("Landscape");
  portraitCheckBox->setEnabled(false);
  landscapeCheckBox->setEnabled(false);
  
  // Connect the two landscape/portrait buttons to their own callback functions
  connect(portraitBtn,SIGNAL(clicked()),this,SLOT(UpdatePortraitCheckbox()));
  connect(landscapeBtn,SIGNAL(clicked()),this,SLOT(UpdateLandscapeCheckbox()));
  UpdatePortraitCheckbox();
  buttonLayout->addWidget(portraitBtn);
  buttonLayout->addWidget(landscapeBtn);
  checkBoxLayout->addWidget(portraitCheckBox);
  checkBoxLayout->addWidget(landscapeCheckBox);
  landscapeLayout->addRow(new QLabel(tr("Image Orientation:")), buttonLayout);
  landscapeLayout->addRow(new QLabel(tr("Current Setting:")), checkBoxLayout);
  
  landscapeGroupBox->setLayout(landscapeLayout);

  visualSettingsLayout->addWidget(methodGroupBox);
  visualSettingsLayout->addWidget(colorGroupBox);
  visualSettingsLayout->addWidget(landscapeGroupBox);
}

void MainWindow::createImageSettingsGroupBox()
{  
  imageSettingsLayout = new QVBoxLayout;


  imageSizeGroupBox = new QGroupBox(tr("Image Size"));
  QFormLayout *sizeLayout = new QFormLayout;
  
  sizeDial = new QDial;  
  imageSizeLCD = new QLCDNumber;
  
  // size dial and size LCD directly connected
  connect(sizeDial,SIGNAL(valueChanged(int)),imageSizeLCD,SLOT(display(int)));
  
  sizeDial->setMinimum(50);
  sizeDial->setMaximum(100);
  imageSizeLCD->setPalette(Qt::red);
  sizeLayout->addRow(new QLabel(tr("Image Size:")), sizeDial);
  sizeLayout->addRow(new QLabel(tr("Current Setting:")), imageSizeLCD);
  imageSizeGroupBox->setLayout(sizeLayout);

  imageBrightnessGroupBox = new QGroupBox(tr("Image Brightness"));
  QFormLayout *brightnessLayout = new QFormLayout;
  brightnessSlider = new QSlider;
  brightnessProgressBar = new QProgressBar;
  
  // Link brightness slider with its progress bar display
  // This was done in a custom function to allow for the numeric brightness value to be displayed
  // alongside the progressbar "precentage"
  connect(brightnessSlider,SIGNAL(valueChanged(int)),this,SLOT(UpdateBrightnessBar()));
  
  // Initialize brightness progress bar display and various widget settings
  UpdateBrightnessBar();  
  brightnessSlider->setOrientation(Qt::Horizontal);
  brightnessSlider->setTickPosition(QSlider::TicksBothSides);
  brightnessSlider->setTickInterval(10);
  brightnessSlider->setSingleStep(1);
  brightnessSlider->setMinimum(0);
  brightnessSlider->setMaximum(255);
  brightnessProgressBar->setMinimum(0);
  brightnessProgressBar->setMaximum(255);
  
  brightnessLayout->addRow(new QLabel(tr("Image Brightness:")), brightnessSlider);
  brightnessLayout->addRow(new QLabel(tr("Current Setting:")), brightnessProgressBar);
  imageBrightnessGroupBox->setLayout(brightnessLayout);

  imageSettingsLayout->addWidget(imageBrightnessGroupBox);
  imageSettingsLayout->addWidget(imageSizeGroupBox);
}
  


// Various slot functions:
void MainWindow::UpdateMethodLineEdit()
{
  for (int i = 0; i < NUM_BUTTONS; ++i) {
    if (methodButtons[i]->isChecked()) {
      methodEdit->setText(methodLabels[i]);
    }
  }
}

void MainWindow::UpdateBrightnessBar()
{
  int brightnessValue = brightnessSlider->value();
  brightnessProgressBar->setValue(brightnessValue);
  brightnessProgressBar->setFormat("%p% ("+QString::number(brightnessValue)+")");
}

void MainWindow::UpdateColorTabBar()
{
  colorRepTabBar->setCurrentIndex(colorRepComboBox->currentIndex());
}

void MainWindow::UpdatePortraitCheckbox()
{
  portraitCheckBox->setChecked(true);
  landscapeCheckBox->setChecked(false);
}
void MainWindow::UpdateLandscapeCheckbox()
{
  portraitCheckBox->setChecked(false);
  landscapeCheckBox->setChecked(true);
}
