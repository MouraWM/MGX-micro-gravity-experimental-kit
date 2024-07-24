from data_processing import testGenerator, saveResult
from tensorflow.keras.models import load_model

model = load_model('model/unet_model.h5')

test_path = "dataset/test"
testGene = testGenerator(test_path)

results = model.predict(testGene, verbose=1)

saveResult("result/", results)
