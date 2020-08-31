pip3 install flask
pip3 install flask_socketio
cd project/project
swig -python rf.i
python3 rf_setup.py build_ext --inplace
cd ../../
