import {Image, StyleSheet, Platform, View} from 'react-native';

import {HelloWave} from '@/components/HelloWave';
import ParallaxScrollView from '@/components/ParallaxScrollView';
import {ThemedText} from '@/components/ThemedText';
import {ThemedView} from '@/components/ThemedView';
import {createBottomTabNavigator} from "@react-navigation/bottom-tabs";
import { studentScreen } from "@/app/(tabs)/student";
import { courseScreen } from "@/app/(tabs)/course";


function HomeScreen() {
    return (
        <ParallaxScrollView
            headerBackgroundColor={{light: '#A1CEDC', dark: '#1D3D47'}}
            headerImage={
                <Image
                    source={require('@/assets/images/partial-react-logo.png')}
                    style={styles.reactLogo}
                />
            }>
            <ThemedView style={styles.stepContainer}>
                <ThemedText type="subtitle">Hello, World!</ThemedText>
                <ThemedText>
                    Very Important Index Page
                </ThemedText>
            </ThemedView>
        </ParallaxScrollView>
    );
}

const Tab = createBottomTabNavigator();

export function Navigation() {
    return (
        <Tab.Navigator>
            <Tab.Screen name="Home" component={HomeScreen} />
            <Tab.Screen name="Students" component={studentScreen} />
            <Tab.Screen name="Courses" component={courseScreen} />
        </Tab.Navigator>
    );
}

export default function App() {
    return (
            <Navigation />
    );
}


const styles = StyleSheet.create({
    titleContainer: {
        flexDirection: 'row',
        alignItems: 'center',
        gap: 8,
    },
    stepContainer: {
        gap: 8,
        marginBottom: 8,
    },
    reactLogo: {
        height: 178,
        width: 290,
        bottom: 0,
        left: 0,
        position: 'absolute',
    },
});
