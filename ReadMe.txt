================================================================================
<<<<<<< HEAD
    MICROSOFT FOUNDATION CLASS LIBRARY : oglLineEdit Project Overview
===============================================================================

The application wizard has created this oglLineEdit application for
=======
    MICROSOFT FOUNDATION CLASS LIBRARY : oglmfcDialog Project Overview
===============================================================================

The application wizard has created this oglmfcDialog application for
>>>>>>> 4556502755a57ee895f72f96f023f82d252e5a82
you.  This application not only demonstrates the basics of using the Microsoft
Foundation Classes but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
<<<<<<< HEAD
make up your oglLineEdit application.

oglLineEdit.vcxproj
=======
make up your oglmfcDialog application.

oglmfcDialog.vcxproj
>>>>>>> 4556502755a57ee895f72f96f023f82d252e5a82
    This is the main project file for VC++ projects generated using an application wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    application wizard.

<<<<<<< HEAD
oglLineEdit.vcxproj.filters
=======
oglmfcDialog.vcxproj.filters
>>>>>>> 4556502755a57ee895f72f96f023f82d252e5a82
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

<<<<<<< HEAD
oglLineEdit.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CoglLineEditApp application class.

oglLineEdit.cpp
    This is the main application source file that contains the application
    class CoglLineEditApp.

oglLineEdit.rc
=======
oglmfcDialog.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CoglmfcDialogApp application class.

oglmfcDialog.cpp
    This is the main application source file that contains the application
    class CoglmfcDialogApp.

oglmfcDialog.rc
>>>>>>> 4556502755a57ee895f72f96f023f82d252e5a82
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++. Your project resources are in 1033.

<<<<<<< HEAD
res\oglLineEdit.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file oglLineEdit.rc.

res\oglLineEdit.rc2
=======
res\oglmfcDialog.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file oglmfcDialog.rc.

res\oglmfcDialog.rc2
>>>>>>> 4556502755a57ee895f72f96f023f82d252e5a82
    This file contains resources that are not edited by Microsoft
    Visual C++. You should place all resources not editable by
    the resource editor in this file.


/////////////////////////////////////////////////////////////////////////////

The application wizard creates one dialog class:

<<<<<<< HEAD
oglLineEditDlg.h, oglLineEditDlg.cpp - the dialog
    These files contain your CoglLineEditDlg class.  This class defines
    the behavior of your application's main dialog.  The dialog's template is
    in oglLineEdit.rc, which can be edited in Microsoft Visual C++.
=======
oglmfcDialogDlg.h, oglmfcDialogDlg.cpp - the dialog
    These files contain your CoglmfcDialogDlg class.  This class defines
    the behavior of your application's main dialog.  The dialog's template is
    in oglmfcDialog.rc, which can be edited in Microsoft Visual C++.
>>>>>>> 4556502755a57ee895f72f96f023f82d252e5a82

/////////////////////////////////////////////////////////////////////////////

Other Features:

ActiveX Controls
    The application includes support to use ActiveX controls.

Printing and Print Preview support
    The application wizard has generated code to handle the print, print setup, and print preview
    commands by calling member functions in the CView class from the MFC library.

/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
<<<<<<< HEAD
    named oglLineEdit.pch and a precompiled types file named StdAfx.obj.
=======
    named oglmfcDialog.pch and a precompiled types file named StdAfx.obj.
>>>>>>> 4556502755a57ee895f72f96f023f82d252e5a82

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

<<<<<<< HEAD
oglLineEdit.manifest
=======
oglmfcDialog.manifest
>>>>>>> 4556502755a57ee895f72f96f023f82d252e5a82
	Application manifest files are used by Windows XP to describe an applications
	dependency on specific versions of Side-by-Side assemblies. The loader uses this
	information to load the appropriate assembly from the assembly cache or private
	from the application. The Application manifest  maybe included for redistribution
	as an external .manifest file that is installed in the same folder as the application
	executable or it may be included in the executable in the form of a resource.
/////////////////////////////////////////////////////////////////////////////

Other notes:

The application wizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, you will need
to redistribute the MFC DLLs. If your application is in a language
other than the operating system's locale, you will also have to
redistribute the corresponding localized resources mfc110XXX.DLL.
For more information on both of these topics, please see the section on
redistributing Visual C++ applications in MSDN documentation.

/////////////////////////////////////////////////////////////////////////////
