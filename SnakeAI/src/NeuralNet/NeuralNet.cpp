#include "NeuralNet.h"

NeuralNet::NeuralNet()
{

}

NeuralNet::NeuralNet(int input, int hidden, int output, int hiddenLayers)
{
    iNodes = input;
    hNodes = hidden;
    oNodes = output;
    hLayers = hiddenLayers;

    weights = std::vector<Matrix>(hLayers + 1);
    weights[0] = Matrix(hNodes, iNodes + 1);
    for (int i = 1; i < hLayers; i++)
        weights[i] = Matrix(hNodes, hNodes + 1);
    weights[weights.size() - 1] = Matrix(oNodes, hNodes + 1);
    for (int i = 0; i < weights.size(); i++)
    {
        weights[i].randomize();
    }
}

void NeuralNet::mutate(float mr)
{
    for (Matrix w : weights)
        w.mutate(mr);
}

std::vector<float> NeuralNet::output(std::vector<float> inputsArr)
{
    Matrix inputs = weights[0].singleColumnMatrixFromArray(inputsArr);
    Matrix curr_bias = inputs.addBias();

    for (int i = 0; i < hLayers; i++) 
    {
        Matrix hidden_ip = weights[i].dot(curr_bias);
        Matrix hidden_op = hidden_ip.activate();
        curr_bias = hidden_op.addBias();
    }
    Matrix output_ip = weights[weights.size() - 1].dot(curr_bias);
    Matrix output = output_ip.activate();
    return output.toArray();
}

NeuralNet NeuralNet::crossover(NeuralNet partner)
{
    NeuralNet child = NeuralNet(iNodes, hNodes, oNodes, hLayers);
    for (int i = 0; i < weights.size(); i++)
        child.weights[i] = weights[i].crossover(partner.weights[i]);
    return child;
}

NeuralNet NeuralNet::clone()
{
    NeuralNet clone = NeuralNet(iNodes, hNodes, oNodes, hLayers);
    for (int i = 0; i < weights.size(); i++)
        clone.weights[i] = weights[i].clone();
    return clone;
}

void NeuralNet::load(std::vector<Matrix> weight)
{
    for (int i = 0; i < weights.size(); i++)
        weights[i] = weight[i];
}

std::vector<Matrix> NeuralNet::pull()
{
    std::vector<Matrix> model;

    for (Matrix m : weights)
        model.push_back(m.clone());
    return model;
}

