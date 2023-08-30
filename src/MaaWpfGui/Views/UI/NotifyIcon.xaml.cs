// <copyright file="NotifyIcon.xaml.cs" company="MaaAssistantArknights">
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

using System.Windows;
using System.Windows.Controls;
using MaaWpfGui.Helper;
using MaaWpfGui.ViewModels.UI;
using Serilog;

namespace MaaWpfGui.Views.UI
{
    /// <summary>
    /// 托盘图标。
    /// </summary>
    public partial class NotifyIcon : System.Windows.Controls.UserControl
    {
        private static readonly ILogger _logger = Log.ForContext<NotifyIcon>();

        public NotifyIcon()
        {
            InitializeComponent();
            InitIcon();
            ToastNotification.ShowBalloonTip = notifyIcon.ShowBalloonTip;
        }

        private void InitIcon()
        {
            notifyIcon.Click += NotifyIcon_MouseClick;
            notifyIcon.MouseDoubleClick += OnNotifyIconDoubleClick;

            startMenu.Click += StartTask;
            stopMenu.Click += StopTask;
            forceShowMenu.Click += ForceShow;
            exitMenu.Click += App_exit;

            foreach (var lang in LocalizationHelper.SupportedLanguages)
            {
                if (lang.Key == SettingsViewModel.PallasLangKey)
                {
                    continue;
                }

                var langMenu = new MenuItem() { Header = lang.Value };
                langMenu.Click += (sender, e) =>
                {
                    Instances.SettingsViewModel.Language = lang.Key;
                };

                switchLangMenu.Items.Add(langMenu);
            }
        }

        private void NotifyIcon_MouseClick(object sender, RoutedEventArgs e)
        {
            Instances.MainWindowManager?.SwitchWindowState();
        }

        private void StartTask(object sender, RoutedEventArgs e)
        {
            // taskQueueViewModel意外为null了是不是也可以考虑Log一下
            // 先放个log点方便跟踪
            Instances.TaskQueueViewModel?.LinkStart();
            _logger.Information("Tray service task started.");
        }

        private void StopTask(object sender, RoutedEventArgs e)
        {
            Instances.TaskQueueViewModel?.Stop();
            _logger.Information("Tray service task stop.");
        }

        private void ForceShow(object sender, RoutedEventArgs e)
        {
            Instances.MainWindowManager?.ForceShow();
            _logger.Information("WindowManager force show.");
        }

        private void App_exit(object sender, RoutedEventArgs e)
        {
            Application.Current.MainWindow.Close();
        }

        private void App_show(object sender, RoutedEventArgs e)
        {
            Instances.MainWindowManager?.Show();
        }

        private void OnNotifyIconDoubleClick(object sender, RoutedEventArgs e)
        {
            Instances.MainWindowManager?.Show();
        }
    }
}