# NeuralVisUAL

NeuralVisUAL (Deep **Neural** Network **Vis**ualization in the **U**nreal Engine for Inter**a**ctive F**l**y-through Exploration) is the first step towards an extensible framework for neural network visualization, facilitating a better understanding of these networks through exploration.
It is a modular application, written in python, C++, and Unreal Engine blueprints, that visualizes any feed-forward deep neural network developed in TensorFlow and Keras.

NeuralVisUE utilizes the force-based algorithm ForceAtlas 2 with some modifications to calculate a meaningful layout of the given network on a two-dimensional plane.
This layout determines where to spawn objects in a virtual game environment, which the user can freely explore, interacting with the network through this application.
Furthermore, the application visualizes the kernels of convolution layers in convoluational neural networks, the corresponding kernel activations, saliency maps, and integrated gradients according to user-defined preferences.

NeuralVisUE consists of several distinct modules connected by precisely defined interface interactions.
Its python server runs on the same machine that hosts the neural network; it is responsible for directly loading and interacting with the network, processing retrieved data into visualizations.
The client contains a custom UE4 C++ plugin for WebSocket interactions, Unreal Engine blueprints to interpret responses, cache data and spawn objects, and the Unreal Engine 4 game environment that renders these visualizations in an interactive world, to be freely explored by the user.
Among other advantages, this allows for a separation between a server interacting with the neural network and an Unreal Engine 4 client that renders the visualization for the user to explore freely.

This project is published under the GNU GPLv3 license.

# Jannik Hofmann master thesis

NeuralVisUAL was developed by Jannik Hofmann as part of his master thesis for the university of Tübingen (Eberhard-Karls-Universität Tübingen).

The theoretical background of this project as well as more detailed information about the implementation can be found in the pdf-file of the thesis itself.
A compressed version of this pdf file is available in this repository. The full [high-quality version of the thesis is here](https://drive.google.com/file/d/1lViMtYSkV5p2BQoxMivBG5NKNootr9Fz/view?usp=sharing).

# Setup

Due to the huge size of UE4 (Unreal Engine 4) projects, only part of the project structure has been uploaded to this repo.

## UE4 Client
To recreate the NeuralVisUAL project, please create a new UE4 project on your own, then overwrite the *Content*, *Plugins*, and *Source* folders of that project with the ones found in the *NeuralVisUE* folder of this repo.

Then, please navigate to NeuralVisUE/Plugins/NeuralInteractionClient/Source/ThirdParty and create a folder BoostLibrary, containing [the boost_1_75_0 folder with the library from boost.org](https://www.boost.org/users/history/version_1_75_0.html).
NeuralVisUE/Plugins/NeuralInteractionClient/Source/ThirdParty/BoostLibrary/boost_1_75_0 should now contain files such as boost.png, README.md and folders boost, doc, more, among others.
You also need to "prepare to use a boost library binary", as described in step 5 of the guide for [Windows](https://www.boost.org/doc/libs/1_75_0/more/getting_started/windows.html) or [Unix](https://www.boost.org/doc/libs/1_75_0/more/getting_started/unix-variants.html).
The complete UE4 project can now be run to start the NeuralVisUAL client.

## Server
For the server, simply execute the *Python Interaction Scripts/centralController.py* file in python.
If python throws errors due to missing libraries, please install the relevant libraries to your python environment.

Any configuration for the server or visualization settings can be made in *serverSettings.py* and *visualizationSettings.py*. To disable features, please set the variables to 0 or False instead of removing or commenting out code lines in the settings.

For further information on how to use the python server, please refer to the thesis pdf or type the commands *help* or *server status* in the console of the running UE4 client.
