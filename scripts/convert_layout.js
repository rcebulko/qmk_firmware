const fs = require('fs');

const REDOX_JSON_PATH = '../keyboards/redox/keymaps/rcebulko/redox_rev1_layout_mine 3x5.json';
const MINIDOX_JSON_PATH = '../keyboards/minidox/keymaps/rcebulko/minidox_layout_split_3x5_mine.json';

const MINIDOX_BASE_CONFIG = {
  "version": 1,
  "author": "Ryan Cebulko",
  "notes": "",
  "documentation": "\"This file is a QMK Configurator export. You can import this at <https://config.qmk.fm>. It can also be used directly with QMK's source code.\n\nTo setup your QMK environment check out the tutorial: <https://docs.qmk.fm/#/newbs>\n\nYou can convert this file to a keymap.c using this command: `qmk json2c {keymap}`\n\nYou can compile this keymap using this command: `qmk compile {keymap}`\"\n",
  "keyboard": "maple_computing/minidox/rev1",
  "keymap": "minidox_layout_split_3x5_mine",
  "layout": "LAYOUT_split_3x5_3",
};

function symmetricSlice(row, start, length) {
  const size = row.length;
  const end = start + length;
  return [
    row.slice(start, end),
    row.slice(size - end, size - start),
  ].flat();
}

function redoxLayerToMinidoxLayer(layer) {
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
  // Each row, excluding the outermost pair of keys
  // const innerRows = rows.map(row => row.slice(1, -1));

  return [
    symmetricSlice(top, 1, 5),
    symmetricSlice(middle, 1, 5),
    symmetricSlice(bottom, 1, 5),
    symmetricSlice(thumbs, 4, 3),
  ].flat();
}

function redoxConfigToMinidoxConfig(config) {
  return {
    ...MINIDOX_BASE_CONFIG,
    layers: config.layers.map(redoxLayerToMinidoxLayer),
  };
}

function redoxJsonToMinidoxJson(json) {
  return JSON.stringify(
    redoxConfigToMinidoxConfig(JSON.parse(json)),
    null,
    2,
  );
}

function convertRedoxToMinidox(redoxPath, minidoxPath) {
  fs.writeFileSync(
    minidoxPath,
    redoxJsonToMinidoxJson(fs.readFileSync(redoxPath)),
  );
}

convertRedoxToMinidox(REDOX_JSON_PATH, MINIDOX_JSON_PATH);
