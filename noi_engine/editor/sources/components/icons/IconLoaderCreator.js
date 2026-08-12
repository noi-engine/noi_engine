.pragma library

.import "MaterialSymbolsRegular/codepoints.js" as MUI

const loaders = {};

function createBaseLoader(name, icons) {
    return {
        name: name,
        icons: icons,
        get(iconName) {
            try {
                const codepoint = icons[iconName];
                return String.fromCodePoint(parseInt(codepoint, 16));
            }
            catch(e){
                console.log("ERRROR=", iconName);
                console.log("The Error = ", e);
            }
        }
    }
}

loaders["mui"] = createBaseLoader("mui", MUI.icons);

function getLoader(name) {
    if (name in loaders) {
        return loaders[name];
    }
    throw new Error("Unsupported Icon Loader: " + name);
}
