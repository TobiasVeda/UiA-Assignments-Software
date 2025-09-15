import {ThemedText} from "@/components/ThemedText";
import {useEffect, useState} from "react";
import {TextInput} from "react-native";

export const DisplayCourses = () => {

    const [code, setCode] = useState('');
    const [name, setName] = useState('');
    const [textareaValue, setTextareaValue] = useState('')


    useEffect(()=>{
        setTextareaValue(code + "-" + name);
    }, [code, name]);

    return (
        <ThemedText>
            <TextInput
                placeholder="Filter Name"
                value={code}
                onChangeText={setCode}
                style={{ borderWidth: 1, padding: 10, marginBottom: 10 }}
            />
            <TextInput
                placeholder="Filter Name"
                value={name}
                onChangeText={setName}
                style={{ borderWidth: 1, padding: 10, marginBottom: 10 }}
            />
            <br/>
            <textarea
                value={textareaValue}
                style={{
                    width: '75%',
                    height: '500%',
                    resize: 'none',
                    padding: '10px',
                    border: '12px solid #ccc'
                }}
            ></textarea>
        </ThemedText>
    );

}