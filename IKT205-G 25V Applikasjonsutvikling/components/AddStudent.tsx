import {ThemedText} from "@/components/ThemedText";
import {useState} from "react";
import {TextInput} from "react-native";
import {addDoc, collection} from "@firebase/firestore";
import {db} from "@/firebaseConfig";

export const AddStudent = () => {

    const [name, setName] = useState("");


        const buttonPressed = async () => {
            if (name == "") {
                console.log("Set a name, dumbass");
                return;
            }

            try {
                await addDoc(collection(db, "students"), {
                    name: "shid"
                });

                console.log("New students document added");
            } catch (e) {
                console.error("Error adding new students document:", e);
            }


        }

        return (
            <ThemedText>
                <TextInput
                    placeholder="Name"
                    value={name}
                    onChangeText={setName}
                    style={{borderWidth: 1, padding: 10, marginBottom: 10}}
                />
                <br/>
                <button onClick={buttonPressed} style={{borderWidth: 1, padding: 10, marginBottom: 10}}>Add Student
                </button>
            </ThemedText>
        );

    }