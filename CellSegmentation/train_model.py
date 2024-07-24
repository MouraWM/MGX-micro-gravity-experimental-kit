from data_processing import trainValGenerator
from segmentation_model import unet, get_callbacks
from plots import plot_training_history

data_gen_args = dict(
    rotation_range=30,
    width_shift_range=0.1,
    height_shift_range=0.1,
    shear_range=0.2,
    zoom_range=0.2,
    horizontal_flip=True,
    vertical_flip=True,
    fill_mode='reflect'
)

trainGen = trainValGenerator(2, 'dataset/train', 'image', 'label', data_gen_args, save_image_to_dir=None, save_label_to_dir=None)
valGen = trainValGenerator(2, 'dataset/val', 'image', 'label', data_gen_args, save_image_to_dir=None, save_label_to_dir=None)

model = unet()
callbacks = get_callbacks('model/unet_model.h5')
history = model.fit(trainGen, validation_data=valGen, epochs=50, steps_per_epoch=100, validation_steps=100, callbacks=callbacks)

plot_training_history(history)
