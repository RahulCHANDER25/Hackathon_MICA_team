import { generateEvent , Args , Storage} from "@massalabs/massa-as-sdk";

export function read_data(_args: string): void {
    let arr_data: Array<string>;
    let type_data: Array<string>;
    type_data = ["Name", "Age", "Group Blood", "Country",
                "Arrangement", "Expiration"];
    arr_data = ["", "", "", "", "", ""];

    for (let i = 0; i < 6; ++i) {
        if (Storage.get(type_data[i]) != "Expired") {
            arr_data[i] = Storage.get(type_data[i]);
            generateEvent(`${arr_data[i]}`);
        }
    }
}

export function stocking_data(stringifyArgs: string): void {
    const args = new Args(stringifyArgs);
    Storage.set("Name", args.nextString());
    Storage.set("Age",  args.nextString());
    Storage.set("Group Blood", args.nextString());  
    Storage.set("Country", args.nextString());
    Storage.set("Arrangement", args.nextString());
    Storage.set("Expiration", args.nextString());
}

export function destroy_arrangement(_args: string): void {
    let a = Storage.get("Expiration");

    if (_args == a) {
        Storage.set("Expiration", "NULL");
        Storage.set("Arrangement", "NULL");
    }
}
