/**************************************************************************
* Otter Browser: Web browser controlled by the user, not vice-versa.
* Copyright (C) 2013 - 2017 Michal Dutkiewicz aka Emdek <michal@emdek.pl>
* Copyright (C) 2014 Piotr Wójcik <chocimier@tlen.pl>
* Copyright (C) 2015 Jan Bajer aka bajasoft <jbajer@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**************************************************************************/

#ifndef OTTER_ACTIONSMANAGER_H
#define OTTER_ACTIONSMANAGER_H

#include <QtCore/QCoreApplication>
#include <QtCore/QVariantMap>
#include <QtGui/QIcon>

namespace Otter
{

class Action;

class ActionsManager : public QObject
{
	Q_OBJECT
	Q_ENUMS(ActionIdentifier)

public:
	enum ActionIdentifier
	{
		RunMacroAction = 0,
		NewTabAction,
		NewTabPrivateAction,
		NewWindowAction,
		NewWindowPrivateAction,
		OpenAction,
		SaveAction,
		CloneTabAction,
		PinTabAction,
		DetachTabAction,
		MaximizeTabAction,
		MinimizeTabAction,
		RestoreTabAction,
		AlwaysOnTopTabAction,
		ClearTabHistoryAction,
		PurgeTabHistoryAction,
		MuteTabMediaAction,
		SuspendTabAction,
		CloseTabAction,
		CloseOtherTabsAction,
		ClosePrivateTabsAction,
		ClosePrivateTabsPanicAction,
		ReopenTabAction,
		MaximizeAllAction,
		MinimizeAllAction,
		RestoreAllAction,
		CascadeAllAction,
		TileAllAction,
		CloseWindowAction,
		SessionsAction,
		SaveSessionAction,
		OpenUrlAction,
		OpenLinkAction,
		OpenLinkInCurrentTabAction,
		OpenLinkInNewTabAction,
		OpenLinkInNewTabBackgroundAction,
		OpenLinkInNewWindowAction,
		OpenLinkInNewWindowBackgroundAction,
		OpenLinkInNewPrivateTabAction,
		OpenLinkInNewPrivateTabBackgroundAction,
		OpenLinkInNewPrivateWindowAction,
		OpenLinkInNewPrivateWindowBackgroundAction,
		OpenLinkInApplicationAction,
		CopyLinkToClipboardAction,
		BookmarkLinkAction,
		SaveLinkToDiskAction,
		SaveLinkToDownloadsAction,
		OpenSelectionAsLinkAction,
		OpenFrameInCurrentTabAction,
		OpenFrameInNewTabAction,
		OpenFrameInNewTabBackgroundAction,
		OpenFrameInApplicationAction,
		CopyFrameLinkToClipboardAction,
		ReloadFrameAction,
		ViewFrameSourceAction,
		OpenImageInNewTabAction,
		OpenImageInNewTabBackgroundAction,
		SaveImageToDiskAction,
		CopyImageToClipboardAction,
		CopyImageUrlToClipboardAction,
		ReloadImageAction,
		ImagePropertiesAction,
		SaveMediaToDiskAction,
		CopyMediaUrlToClipboardAction,
		MediaControlsAction,
		MediaLoopAction,
		MediaPlayPauseAction,
		MediaMuteAction,
		FillPasswordAction,
		GoAction,
		GoBackAction,
		GoForwardAction,
		GoToPageAction,
		GoToHomePageAction,
		GoToParentDirectoryAction,
		RewindAction,
		FastForwardAction,
		StopAction,
		StopScheduledReloadAction,
		StopAllAction,
		ReloadAction,
		ReloadOrStopAction,
		ReloadAndBypassCacheAction,
		ReloadAllAction,
		ScheduleReloadAction,
		ContextMenuAction,
		UndoAction,
		RedoAction,
		CutAction,
		CopyAction,
		CopyPlainTextAction,
		CopyAddressAction,
		CopyToNoteAction,
		PasteAction,
		PasteAndGoAction,
		PasteNoteAction,
		DeleteAction,
		SelectAllAction,
		UnselectAction,
		ClearAllAction,
		CheckSpellingAction,
		SelectDictionaryAction,
		FindAction,
		FindNextAction,
		FindPreviousAction,
		QuickFindAction,
		SearchAction,
		CreateSearchAction,
		ZoomInAction,
		ZoomOutAction,
		ZoomOriginalAction,
		ScrollToStartAction,
		ScrollToEndAction,
		ScrollPageUpAction,
		ScrollPageDownAction,
		ScrollPageLeftAction,
		ScrollPageRightAction,
		StartDragScrollAction,
		StartMoveScrollAction,
		EndScrollAction,
		PrintAction,
		PrintPreviewAction,
		ActivateAddressFieldAction,
		ActivateSearchFieldAction,
		ActivateContentAction,
		ActivatePreviouslyUsedTabAction,
		ActivateLeastRecentlyUsedTabAction,
		ActivateTabAction,
		ActivateTabOnLeftAction,
		ActivateTabOnRightAction,
		BookmarksAction,
		BookmarkPageAction,
		BookmarkAllOpenPagesAction,
		OpenBookmarkAction,
		QuickBookmarkAccessAction,
		CookiesAction,
		LoadPluginsAction,
		EnableJavaScriptAction,
		EnableReferrerAction,
		ViewSourceAction,
		OpenPageInApplicationAction,
		InspectPageAction,
		InspectElementAction,
		WorkOfflineAction,
		FullScreenAction,
		ShowTabSwitcherAction,
		ShowMenuBarAction,
		ShowTabBarAction,
		ShowSidebarAction,
		ShowErrorConsoleAction,
		LockToolBarsAction,
		ResetToolBarsAction,
		OpenPanelAction,
		ClosePanelAction,
		ContentBlockingAction,
		HistoryAction,
		ClearHistoryAction,
		AddonsAction,
		NotesAction,
		PasswordsAction,
		TransfersAction,
		PreferencesAction,
		WebsitePreferencesAction,
		QuickPreferencesAction,
		ResetQuickPreferencesAction,
		WebsiteInformationAction,
		WebsiteCertificateInformationAction,
		SwitchApplicationLanguageAction,
		CheckForUpdatesAction,
		DiagnosticReportAction,
		AboutApplicationAction,
		AboutQtAction,
		ExitAction,
		OtherAction
	};

	struct ActionDefinition
	{
		enum ActionFlag
		{
			NoFlags = 0,
			IsEnabledFlag = 1,
			IsCheckableFlag = 2,
			IsCheckedFlag = 4,
			HasMenuFlag = 8
		};

		Q_DECLARE_FLAGS(ActionFlags, ActionFlag)

		struct State
		{
			QString text;
			QString description;
			QIcon icon;
			bool isEnabled = true;
			bool isChecked = false;
		};

		State defaultState;
		QVector<QKeySequence> shortcuts;
		int identifier = -1;
		ActionFlags flags = IsEnabledFlag;

		QString getText(bool preferDescription = false) const
		{
			return QCoreApplication::translate("actions", ((preferDescription && !defaultState.description.isEmpty()) ? defaultState.description : defaultState.text).toUtf8().constData());
		}
	};

	struct ActionEntryDefinition
	{
		QString action;
		QVariantMap options;
		QVariantMap parameters;
		QVector<ActionEntryDefinition> entries;
	};

	static void createInstance(QObject *parent);
	static void loadProfiles();
	static void triggerAction(int identifier, QObject *parent, const QVariantMap &parameters = QVariantMap());
	static ActionsManager* getInstance();
	static Action* getAction(int identifier, QObject *parent);
	static QString getReport();
	static QString getActionName(int identifier);
	static QVector<ActionDefinition> getActionDefinitions();
	static ActionDefinition getActionDefinition(int identifier);
	static int getActionIdentifier(const QString &name);

protected:
	explicit ActionsManager(QObject *parent);

	void timerEvent(QTimerEvent *event) override;
	static void registerAction(int identifier, const QString &text, const QString &description = QString(), const QIcon &icon = QIcon(), ActionDefinition::ActionFlags flags = ActionDefinition::IsEnabledFlag);

protected slots:
	void handleOptionChanged(int identifier);

signals:
	void shortcutsChanged();

private:
	int m_reloadTimer;

	static ActionsManager *m_instance;
	static QVector<ActionDefinition> m_definitions;
	static int m_actionIdentifierEnumerator;
};

}

Q_DECLARE_OPERATORS_FOR_FLAGS(Otter::ActionsManager::ActionDefinition::ActionFlags)

#endif
