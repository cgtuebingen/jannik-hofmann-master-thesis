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

# Jannik Hofmann master thesis

NeuralVisUAL was developed by Jannik Hofmann as part of his master thesis for the university of Tübingen (Eberhard-Karls-Universität Tübingen).

The theoretical background of this project as well as more detailed information about the implementation can be found in the pdf-file of the thesis itself.
