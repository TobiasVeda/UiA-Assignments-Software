import { View, Text, StyleSheet } from 'react-native';
import { AddStudent } from "@/components/AddStudent";
import { DisplayStudents } from "@/components/DisplayStudents";

export function studentScreen() {



    return (
        <View
            style={[
                styles.container,
                {
                    flexDirection: 'row',
                },
            ]}>
            <View style={{flex: 1, backgroundColor: 'red'}}>
                <AddStudent/>
            </View>
            <View style={{flex: 1, backgroundColor: 'darkorange'}}>
                <DisplayStudents/>
            </View>
        </View>
    );
}


const styles = StyleSheet.create({
    container: {
        flex: 1,
        marginTop: 8,
        backgroundColor: 'aliceblue',
    },
    box: {
        width: 50,
        height: 50,
    },
    row: {
        flexDirection: 'row',
        flexWrap: 'wrap',
    },
    button: {
        paddingHorizontal: 8,
        paddingVertical: 6,
        borderRadius: 4,
        backgroundColor: 'oldlace',
        alignSelf: 'flex-start',
        marginHorizontal: '1%',
        marginBottom: 6,
        minWidth: '48%',
        textAlign: 'center',
    },
    selected: {
        backgroundColor: 'coral',
        borderWidth: 0,
    },
    buttonLabel: {
        fontSize: 12,
        fontWeight: '500',
        color: 'coral',
    },
    selectedLabel: {
        color: 'white',
    },
    label: {
        textAlign: 'center',
        marginBottom: 10,
        fontSize: 24,
    },
});