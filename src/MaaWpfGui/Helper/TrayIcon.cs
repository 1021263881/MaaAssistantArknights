// <copyright file="TrayIcon.cs" company="MaaAssistantArknights">
// MaaWpfGui - A part of the MaaCoreArknights project
// Copyright (C) 2021 MistEO and Contributors
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY
// </copyright>

using System;
using System.Windows.Forms;
using StyletIoC;

namespace MaaWpfGui
{
    /// <summary>
    /// 托盘图标。
    /// </summary>
    public partial class TrayIcon
    {
        private readonly IMainWindowManager _mainWindowManager;
        private readonly NotifyIcon notifyIcon = new NotifyIcon();
        private readonly TaskQueueViewModel _taskQueueViewModel;
        private readonly SettingsViewModel _settingsViewModel;

        /// <summary>
        /// Initializes a new instance of the <see cref="TrayIcon"/> class.
        /// </summary>
        /// <param name="container">The IoC container.</param>
        public TrayIcon(IContainer container)
        {
            _mainWindowManager = container.Get<IMainWindowManager>();
            _taskQueueViewModel = container.Get<TaskQueueViewModel>();
            _settingsViewModel = container.Get<SettingsViewModel>();
            InitIcon();
            this.SetVisible(true);
        }

        private void InitIcon()
        {
            this.notifyIcon.Text = "MaaAssistantArknights";
            this.notifyIcon.Icon = System.Drawing.Icon.ExtractAssociatedIcon(System.Windows.Forms.Application.ExecutablePath);
            notifyIcon.MouseClick += NotifyIcon_MouseClick;
            notifyIcon.MouseDoubleClick += OnNotifyIconDoubleClick;

            MenuItem startMenu = new MenuItem(Localization.GetString("Farming"));
            startMenu.Click += StartTask;
            MenuItem stopMenu = new MenuItem(Localization.GetString("Stop"));
            stopMenu.Click += StopTask;

            MenuItem switchLangMenu = new MenuItem(Localization.GetString("SwitchLanguage"));

            foreach (var lang in Localization.SupportedLanguages)
            {
                if (lang.Key == SettingsViewModel.PallasLangKey)
                {
                    continue;
                }

                var langMenu = new MenuItem(lang.Value);
                langMenu.Click += (sender, e) =>
                {
                    _settingsViewModel.Language = lang.Key;
                };
                switchLangMenu.MenuItems.Add(langMenu);
            }

            MenuItem exitMenu = new MenuItem(Localization.GetString("Exit"));
            exitMenu.Click += App_exit;
            MenuItem[] menuItems = new MenuItem[] { startMenu, stopMenu, switchLangMenu, exitMenu };
            this.notifyIcon.ContextMenu = new ContextMenu(menuItems);
        }

        private void NotifyIcon_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left)
            {
                return;
            }

            _mainWindowManager.SwitchWindowState();
        }

        private void StartTask(object sender, EventArgs e)
        {
            // taskQueueViewModel意外为null了是不是也可以考虑Log一下
            _taskQueueViewModel?.LinkStart();
        }

        private void StopTask(object sender, EventArgs e)
        {
            _taskQueueViewModel?.Stop();
        }

        private void App_exit(object sender, EventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }

        private void App_show(object sender, EventArgs e)
        {
            _mainWindowManager.Show();
        }

        private void OnNotifyIconDoubleClick(object sender, EventArgs e)
        {
            _mainWindowManager.Show();
        }

        /// <summary>
        /// Sets visibility.
        /// </summary>
        /// <param name="visible">Whether it is visible.</param>
        public void SetVisible(bool visible)
        {
            notifyIcon.Visible = visible;
        }

        /// <summary>
        /// Closes this instance.
        /// </summary>
        public void Close()
        {
            notifyIcon.Icon = null;
            notifyIcon.Visible = false;
            notifyIcon.Dispose();
        }
    }
}
