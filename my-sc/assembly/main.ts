import { Args , call, Address, generateEvent, fileToBase64, createSC } from "@massalabs/massa-as-sdk";
import { append } from "@massalabs/massa-as-sdk/assembly/std/storage";

export function main(): i32 {
   const bytes = fileToBase64('./build/stock.wasm');
   let adress = createSC(bytes);
   let msg: string;

	if(adress.isValid()) {
		msg = "Contract deployed at address:";
	} else {
		msg = "createSC returned an invalid address:";
	}
	generateEvent(`${msg} ${adress.toByteString()}`);
   call(
      adress,
      "stocking_data",
      new Args()
         .add("CHANDER Rahul")
         .add("18")
         .add("O-")
         .add("FR")
         .add("arrangement_CHANDER_Rahul")
         .add("21 NOV 2022")
      , 1_000_000_000
      );
   call(adress, "read_data", new Args("" as string), 1_000_000_000);
   call(adress, "destroy_arrangement", new Args("21 JANV 2022"), 1_000_000_000);
   return 0;
}
