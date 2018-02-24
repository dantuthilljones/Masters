#Run this file with 'source paraview.sh' so that the exports work
export QT_PLUGIN_PATH=/home/dan/Qt/5.9.2/gcc_64/plugins
export PV_PLUGIN_DEBUG=on
mv /home/dan/Qt/5.9.2/gcc_64/plugins/platformthemes/libqgtk3.so /home/dan/Documents/platformthemes
( sleep 5 && mv /home/dan/Documents/platformthemes/libqgtk3.so /home/dan/Qt/5.9.2/gcc_64/plugins/platformthemes ) &
./Documents/ParaView/paraview_build/bin/paraview
