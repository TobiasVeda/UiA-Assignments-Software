import {ThemedText} from "@/components/ThemedText";
import {useState} from "react";
import {TextInput} from "react-native";
import {addDoc, collection, doc, setDoc} from "@firebase/firestore";
import {db} from "@/firebaseConfig";

export const AddCourse = () => {

    const [code, setCode] = useState('');
    const [name, setName] = useState('');

    const buttonPressed = async () => {
        if ((code == "" && name == "")){
            console.log("Set code AND name, dumbass. ");
            return;
        } else if (code == "" && name != ""){
            console.log("Set a code, dumbass");
            return;
        } else if (code != "" && name == ""){
            console.log("Set a name, dumbass");
            return;
        }

        try {
            await addDoc(collection(db, "courses"), {
                code: "a",
                name: "shid"
            });

            console.log("New courses document added");
        } catch (e) {
            console.error("Error adding new course document:", e);
        }


    }

    return (
        <ThemedText>
            <TextInput
                placeholder="Code"
                value={code}
                onChangeText={setCode}
                style={{ borderWidth: 1, padding: 10, marginBottom: 10 }}
            />
            <br/>
            <TextInput
                placeholder="Name"
                value={name}
                onChangeText={setName}
                style={{ borderWidth: 1, padding: 10, marginBottom: 10 }}
            />
            <br/>
            <button onClick={buttonPressed} style={{ borderWidth: 1, padding: 10, marginBottom: 10 }}>Add Course</button>
        </ThemedText>
    );

}