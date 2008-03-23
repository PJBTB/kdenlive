/***************************************************************************
 *   Copyright (C) 2007 by Jean-Baptiste Mardelle (jb@kdenlive.org)        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA          *
 ***************************************************************************/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QUndoView>
#include <QLabel>
#include <QProgressBar>
#include <QEvent>

#include <KXmlGuiWindow>
#include <KTextEdit>
#include <KListWidget>
#include <KTabWidget>
#include <KUndoStack>
#include <KRecentFilesAction>
#include <KComboBox>

#include "ui_timelinebuttons_ui.h"
#include "effectslist.h"
#include "gentime.h"
class KdenliveDoc;
class TrackView;
class MonitorManager;
class ProjectList;
class EffectsListView;
class EffectStackView;
class TransitionSettings;
class Monitor;
class RecMonitor;
class CustomTrackView;
class RenderWidget;
class JogShuttle;
class DocClipBase;

class MainWindow : public KXmlGuiWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void parseProfiles();

protected:
    virtual bool queryClose();
    virtual void customEvent(QEvent * e);

private:
    KTabWidget* m_timelineArea;
    QProgressBar *statusProgressBar;
    QLabel* statusLabel;
    void setupActions();
    KdenliveDoc *m_activeDocument;
    TrackView *m_activeTimeline;
    MonitorManager *m_monitorManager;

    QDockWidget *projectListDock;
    ProjectList *m_projectList;

    QDockWidget *effectListDock;
    EffectsListView *m_effectList;
    //KListWidget *m_effectList;

    QDockWidget *effectStackDock;
    EffectStackView *effectStack;

    QDockWidget *transitionConfigDock;
    TransitionSettings *transitionConfig;

    QDockWidget *clipMonitorDock;
    Monitor *m_clipMonitor;

    QDockWidget *projectMonitorDock;
    Monitor *m_projectMonitor;

    QDockWidget *recMonitorDock;
    RecMonitor *m_recMonitor;

    QDockWidget *undoViewDock;
    QUndoView *m_undoView;
    QUndoGroup *m_commandStack;

    KComboBox *m_timecodeFormat;

    QDockWidget *overviewDock;
    CustomTrackView *m_overView;

    EffectsList m_videoEffects;
    EffectsList m_audioEffects;
    EffectsList m_customEffects;
    EffectsList m_transitions;

    QMenu *m_timelineContextMenu;
    QMenu *m_timelineContextClipMenu;
    QMenu *m_timelineContextTransitionMenu;

    RenderWidget *m_renderWidget;
    Ui::TimelineButtons_UI timeline_buttons_ui;

    JogShuttle *m_jogProcess;

    KRecentFilesAction *m_fileOpenRecent;
    void readOptions();
    void saveOptions();
    void activateShuttleDevice();
    void slotShuttleAction(int code);

public slots:
    void openFile(const KUrl &url);

private slots:
    void newFile();
    void undo();
    void redo();
    void queryQuit();
    void activateDocument();
    void connectDocument(TrackView*, KdenliveDoc*);
    void openFile();
    void saveFile();
    void saveFileAs();
    void saveFileAs(const QString &outputFileName);
    void slotPreferences();
    void updateConfiguration();
    void slotConnectMonitors();
    void slotRaiseMonitor(bool clipMonitor);
    void slotSetClipDuration(int id, int duration);
    void slotUpdateMousePosition(int pos);
    void slotAddEffect(QDomElement effect, GenTime pos = GenTime(), int track = -1);
    void slotEditProfiles();
    void slotEditProjectSettings();
    void slotDisplayActionMessage(QAction *a);
    void slotGotProgressInfo(KUrl url, int progress);
    void slotSwitchVideoThumbs();
    void slotSwitchAudioThumbs();
    void slotRenderProject();
    void slotDoRender(const QString &dest, const QString &render, const QStringList &avformat_args, bool zoneOnly, bool playAfter);
    void slotFullScreen();
    void slotUpdateDocumentState(bool modified);
    void slotZoomIn();
    void slotZoomOut();
    void slotFitZoom();
    void slotRemoveTab();
    void slotDeleteTimelineClip();
    void slotAddVideoEffect(QAction *result);
    void slotAddAudioEffect(QAction *result);
    void slotAddCustomEffect(QAction *result);
    void slotAddProjectClip(KUrl url);
    void slotShuttleButton(int code);
    void slotShowClipProperties(DocClipBase *clip);
};

#endif
