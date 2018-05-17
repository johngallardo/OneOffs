using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

using NativeRuntimeEventSource;
using System.Diagnostics;
using System.Threading.Tasks;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace EventTest
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        int signaled = 0;

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var timer = new Timer(1);
            timer.Ticked += Ticked;
            timer.Start();
        }

        private async void Ticked(Timer sender, object args)
        {
            await this.Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, () =>
            {
                ++signaled;
                Signal.Text = $"Signaled {signaled} times.";
            });
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            GC.Collect();
        }

        private async void Button_Click_2(object sender, RoutedEventArgs e)
        {
            var doodad = new AsyncDooDad();
            await Task.Run( async () => {
                var person = await doodad.GetPersonAsync("John", "Gallardo");
                Debug.WriteLine($"Person is named {person.FirstName} {person.LastName}");
            });
        }
    }
}
