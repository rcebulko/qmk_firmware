const fs = require('fs');

const SHARED_CONFIG = {
  'version': 1,
  'author': 'Ryan Cebulko',
  'notes': '',
  'documentation': "\"This file is a QMK Configurator export. You can import this at <https://config.qmk.fm>. It can also be used directly with QMK's source code.\n\nTo setup your QMK environment check out the tutorial: <https://docs.qmk.fm/#/newbs>\n\nYou can convert this file to a keymap.c using this command: `qmk json2c {keymap}`\n\nYou can compile this keymap using this command: `qmk compile {keymap}`\"\n",
};

const layoutPath = name => `../keyboards/${name}/keymaps/rcebulko/layout.json`;

function symmetricSlice(row, start, length) {
  const size = row.length;
  const end = start + length;
  return [
    row.slice(start, end),
    row.slice(size - end, size - start),
  ].flat();
}

function makeTransformedConfig(fromConfig, baseConfig, layerTransform) {
  return {
    ...SHARED_CONFIG,
    ...baseConfig,
    layers: fromConfig.layers.map(layerTransform),
  };
}

function applyLayoutTransform(fromLayout, toLayout, baseConfig, layerTransform) {
  const fromConfig = JSON.parse(fs.readFileSync(layoutPath(fromLayout)));
  const toConfig = makeTransformedConfig(fromConfig, baseConfig, layerTransform);
  fs.writeFileSync(layoutPath(toLayout), JSON.stringify(toConfig, null, 2));
}

applyLayoutTransform(
  'redox', 'minidox', {
    'keyboard': 'maple_computing/minidox/rev1',
    'layout': 'LAYOUT_split_3x5_3',
    'keymap': 'minidox_layout'
  },
  (layer) => {
    const [, top, middle, bottom, thumbs] = [
      layer.splice(0, 12), // 0: Top row, excluding middle pair
      layer.splice(0, 14), // 1: Next row down + middle pair
      layer.splice(0, 14), // 2: Middle row incl. weird center mods
      layer.splice(0, 16), // 3: Next row down + four top thumb buttons
      layer.splice(0, 14), // 4: Bottom row, 4 mods + 3 thumbs each side
    ];
    if (layer.length) {
      throw new Error(`Layer still has ${layer.length} entries: ${layer}`);
    }

    const [lt0, lt1, lt2, rt2, rt1, rt0] = symmetricSlice(thumbs, 4, 3);
    return [
      symmetricSlice(top, 1, 5),
      symmetricSlice(middle, 1, 5),
      symmetricSlice(bottom, 1, 5),
      [lt2, lt0, lt1, rt1, rt0, rt2],
    ].flat();
  }
);
